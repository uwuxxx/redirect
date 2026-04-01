#pragma once
#include <string>
#include <vector>
#include "Options.h"

namespace URLs
{
	inline std::vector<std::string> Hybrid =
	{
		"fortnite-public-service-prod11.ol.epicgames.com",
		"fortnite-public-service-prod11-matchmaking.ol.epicgames.com",
		"account-public-service-prod03.ol.epicgames.com",
		"friends-public-service-prod06.ol.epicgames.com",
		"party-service-prod.ol.epicgames.com",
		"lightswitch-public-service-prod06.ol.epicgames.com",
		"caldera-service-prod.ol.epicgames.com",
		"fngw-mcp-gcp-playerdata.ol.epicgames.com"
	};

	inline std::vector<std::string> Dev =
	{
		"fortnite-public-service-prod11.ol.epicgames.com",
		"fortnite-public-service-prod11-matchmaking.ol.epicgames.com",
		"account-public-service-prod03.ol.epicgames.com",
		"friends-public-service-prod06.ol.epicgames.com",
		"party-service-prod.ol.epicgames.com",
		"lightswitch-public-service-prod06.ol.epicgames.com",
		"caldera-service-prod.ol.epicgames.com",
		"fngw-mcp-gcp-playerdata.ol.epicgames.com",
		"fngw-mcp-gcp-playerdata2.ol.epicgames.com",
		"fortnite-public-service-stage.ol.epicgames.com"
	};

	inline std::vector<std::string> All =
	{
		".ol.epicgames.com",
		".epicgames.com",
		".fortnite.com"
	};

	inline std::vector<std::string>& Get()
	{
		switch (options::Mode)
		{
		case options::UrlMode::Dev:    return Dev;
		case options::UrlMode::All:    return All;
		default:                       return Hybrid;
		}
	}

	inline bool ShouldRedirect(const std::string& url)
	{
		for (auto& entry : Get())
		{
			if (url.find(entry) != std::string::npos)
				return true;
		}
		return false;
	}
}
