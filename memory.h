#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <optional>
#include <psapi.h>

namespace Memory
{
	inline std::optional<uintptr_t> FindPattern(const char* pattern, const char* mask)
	{
		MODULEINFO info{};
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(nullptr), &info, sizeof(info));

		auto base = reinterpret_cast<uintptr_t>(info.lpBaseOfDll);
		size_t size = info.SizeOfImage;

		size_t patLen = strlen(mask);

		for (size_t i = 0; i < size - patLen; i++)
		{
			bool found = true;
			for (size_t j = 0; j < patLen; j++)
			{
				if (mask[j] != '?' && pattern[j] != *reinterpret_cast<char*>(base + i + j))
				{
					found = false;
					break;
				}
			}

			if (found)
				return base + i;
		}

		return std::nullopt;
	}

	template<typename T>
	inline T Read(uintptr_t address)
	{
		return *reinterpret_cast<T*>(address);
	}

	inline bool Patch(uintptr_t address, std::vector<uint8_t> bytes)
	{
		DWORD old;
		if (!VirtualProtect(reinterpret_cast<void*>(address), bytes.size(), PAGE_EXECUTE_READWRITE, &old))
			return false;

		memcpy(reinterpret_cast<void*>(address), bytes.data(), bytes.size());
		VirtualProtect(reinterpret_cast<void*>(address), bytes.size(), old, &old);
		return true;
	}

	inline bool WriteString(uintptr_t address, const std::string& str)
	{
		DWORD old;
		if (!VirtualProtect(reinterpret_cast<void*>(address), str.size() + 1, PAGE_EXECUTE_READWRITE, &old))
			return false;

		memcpy(reinterpret_cast<void*>(address), str.c_str(), str.size() + 1);
		VirtualProtect(reinterpret_cast<void*>(address), str.size() + 1, old, &old);
		return true;
	}
}
