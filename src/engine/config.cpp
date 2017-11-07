/*
MIT License

Copyright (c) 2017 SAE Institute Switzerland AG

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
//Externals includes
#include "json.hpp"
//STL includes
#include <fstream>
//SFGE includes
#include <engine/config.h>
#include <engine/log.h>

// for convenience
using json = nlohmann::json;

namespace sfge
{

Configuration* ConfigManager::LoadConfig(std::string configFilename)
{
	Configuration* newConfig = new Configuration();
	std::ifstream inputFile(configFilename.c_str());
	if (inputFile.peek() == std::ifstream::traits_type::eof())
	{
		Log::GetInstance()->Error("EMPTY CONFIG FILE");
		return newConfig;
	}
	json jsonConfig;
	try
	{
		inputFile >> jsonConfig;
	}
	catch (json::parse_error& e)
	{
		Log::GetInstance()->Error("THE CONFIG FILE IS NOT JSON");
		return newConfig;
	}

	newConfig->screenResolution = sf::Vector2i(
		jsonConfig["screenResolution"]["x"],
		jsonConfig["screenResolution"]["y"]);

	newConfig->maxFramerate = jsonConfig["maxFramerate"];
	for(const std::string& scene : jsonConfig["scenesList"])
	{
		newConfig->scenesList.push_back(scene);
	}

	return newConfig;
}

}
