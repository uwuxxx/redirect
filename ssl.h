#pragma once
#include <Windows.h>
#include <winhttp.h>
#include <string>
#include "detours.h"
#pragma comment(lib, "winhttp.lib")
namespace SSL
{
	using fnWinHttpOpen = HINTERNET(WINAPI*)(LPCWSTR, DWORD, LPCWSTR, LPCWSTR, DWORD);
	using fnWinHttpConnect = HINTERNET(WINAPI*)(HINTERNET, LPCWSTR, INTERNET_PORT, DWORD);
	using fnWinHttpSetOption = BOOL(WINAPI*)(HINTERNET, DWORD, LPVOID, DWORD);
	using fnWinHttpSendRequest = BOOL(WINAPI*)(HINTERNET, LPCWSTR, DWORD, LPVOID, DWORD, DWORD, DWORD_PTR);
	inline fnWinHttpConnect oWinHttpConnect = nullptr;
	inline fnWinHttpSetOption oWinHttpSetOption = nullptr;
	inline HINTERNET WINAPI hkWinHttpConnect(HINTERNET hSession, LPCWSTR pswzServerName, INTERNET_PORT nServerPort, DWORD dwReserved)
	{
		std::wstring server(pswzServerName);
		std::string narrow(server.begin(), server.end());
		if (URLs::ShouldRedirect(narrow))
		{
			std::wstring backendHost;
			INTERNET_PORT backendPort = 3551;
			std::string backend = options::Backend;
			size_t schemeEnd = backend.find("://");
			if (schemeEnd != std::string::npos)
				backend = backend.substr(schemeEnd + 3);
			size_t portSep = backend.rfind(':');
			if (portSep != std::string::npos)
			{
				backendPort = static_cast<INTERNET_PORT>(std::stoi(backend.substr(portSep + 1)));
				backend = backend.substr(0, portSep);
			}
			backendHost = std::wstring(backend.begin(), backend.end());
			return oWinHttpConnect(hSession, backendHost.c_str(), backendPort, dwReserved);
		}
		return oWinHttpConnect(hSession, pswzServerName, nServerPort, dwReserved);
	}
	inline BOOL WINAPI hkWinHttpSetOption(HINTERNET hInternet, DWORD dwOption, LPVOID lpBuffer, DWORD dwBufferLength)
	{
		if (dwOption == WINHTTP_OPTION_SECURITY_FLAGS)
		{
			DWORD flags = SECURITY_FLAG_IGNORE_ALL_CERT_ERRORS;
			return oWinHttpSetOption(hInternet, dwOption, &flags, sizeof(flags));
		}
		return oWinHttpSetOption(hInternet, dwOption, lpBuffer, dwBufferLength);
	}
	inline bool Init()
	{
		HMODULE winhttp = GetModuleHandleA("winhttp.dll");
		if (!winhttp)
			winhttp = LoadLibraryA("winhttp.dll");
		if (!winhttp