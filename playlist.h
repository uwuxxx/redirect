#pragma once
#include <string>
#include <Windows.h>

namespace Playlist
{
	inline std::string ArenaPlaylistId = "Playlist_ShowdownAlt_Trios";

	inline std::string BuildArenaEntry()
	{
		return R"({
			"playlistName": ")" + ArenaPlaylistId + R"(",
			"maxTeamCount": 100,
			"maxTeamSize": 1,
			"allowJoinInProgress": false,
			"isDefaultPlaylist": false,
			"regions": ["NAE"],
			"gameSessionQueueStatus": "Enabled",
			"bIsRanked": true,
			"divisionColorMappings": [
				{"division": 0, "color": "#7F7F7F"},
				{"division": 1, "color": "#3F9142"},
				{"division": 2, "color": "#2C6FBF"},
				{"division": 3, "color": "#8B3AB5"},
				{"division": 4, "color": "#E5C400"},
				{"division": 5, "color": "#E5C400"},
				{"division": 6, "color": "#E5C400"},
				{"division": 7, "color": "#E5C400"}
			]
		})";
	}

	inline bool IsMatchmakingRequest(const std::string& url)
	{
		return url.find("matchmaking") != std::string::npos
			|| url.find("playlist") != std::string::npos;
	}

	inline std::string PatchArenaResponse(const std::string& body)
	{
		if (body.find("bIsRanked") != std::string::npos)
			return body;

		std::string patched = body;
		size_t pos = patched.rfind(']');
		if (pos != std::string::npos)
		{
			patched.insert(pos, "," + BuildArenaEntry());
		}

		return patched;
	}
}
