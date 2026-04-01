#pragma once
#include <Windows.h>
#include <cstdio>
#include <string>

namespace Console
{
	inline void Init()
	{
		AllocConsole();
		SetConsoleTitleA("redirect");

		FILE* f;
		freopen_s(&f, "CONOUT$", "w", stdout);
		freopen_s(&f, "CONOUT$", "w", stderr);
	}

	inline void Log(const std::string& msg)
	{
		printf("[redirect] %s\n", msg.c_str());
	}

	inline void Warn(const std::string& msg)
	{
		printf("[redirect][warn] %s\n", msg.c_str());
	}

	inline void Free()
	{
		FreeConsole();
	}
}
