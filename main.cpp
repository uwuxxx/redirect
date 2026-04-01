#include <Windows.h>
#include "Options.h"
#include "Console.h"
#include "URLs.h"
#include "SSL.h"
#include "Playlist.h"
#include "Memory.h"

DWORD WINAPI Init(LPVOID)
{
	if (options::Console)
		Console::Init();

	Console::Log("initializing");

	if (!SSL::Init())
	{
		Console::Warn("ssl hook failed");
		return 1;
	}

	Console::Log("backend: " + options::Backend);

	if (options::ArenaPlaylist)
		Console::Log("arena playlist enabled: " + Playlist::ArenaPlaylistId);

	Console::Log("ready");
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD reason, LPVOID)
{
	if (reason == DLL_PROCESS_ATTACH)
		CreateThread(nullptr, 0, Init, nullptr, 0, nullptr);
	else if (reason == DLL_PROCESS_DETACH)
		SSL::Shutdown();

	return TRUE;
}
