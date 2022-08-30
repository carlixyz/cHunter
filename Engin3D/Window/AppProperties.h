#pragma once


#include <string>
#include "../Utility/Utils.h"
#include <assert.h>
#include <yaml-cpp/yaml.h>

struct ApplicationProperties
{
	std::string ApplicationName = "Test 1";
	unsigned Width = 640;
	unsigned Height = 480;
	unsigned Bits = 16;
	bool Fullscreen = false;

	inline void LoadConfiguration(const char* filename)
	{

		YAML::Node configFile = YAML::LoadFile(filename);	// load file
		assert(!configFile.IsNull());						// a shortcut!

		YAML::Node AppNode = configFile["Application"];	// as a Map;

		if (AppNode)
		{
			DEBUG_OUT("App in: " << "\n");

			YAML::Node WinNode = AppNode["Window"];		// .as<YAML::Node>();

			if (WinNode)
			{
														// iterate over bar node to get Property nodes
				for (auto i = WinNode.begin(); i != WinNode.end(); ++i)
				{
					YAML::Node prop = i->second;		// this node is a list of pairs
					DEBUG_OUT("	Win in: " << i->first << ": \n");

					for (const auto& j : prop)
						DEBUG_OUT("		" << j.first << ": " << j.second << "\n");
				}
			}

			if (!configFile.IsNull())					//config["Window"])
			{
				DEBUG_OUT(" YAML ENDED \n");
			}
		}
	}

};

