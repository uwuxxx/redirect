#pragma once
#include <string>

namespace options
{
	inline std::string Backend = "http://127.0.0.1:3551"; 

	enum class UrlMode
	{
		Hybrid,
		Dev,
		All
	};

	inline UrlMode Mode = UrlMode::Hybrid;
	inline bool Console = false;
	inline bool ArenaPlaylist = true;
}
