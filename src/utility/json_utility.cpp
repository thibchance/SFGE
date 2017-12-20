
#include <utility/json_utility.h>
#include <engine/log.h>

#include <fstream>
#include <string>

namespace sfge
{
bool CheckJsonParameter(const json & jsonObject, std::string parameterName, json::value_t expectedType)
{
	return jsonObject.find(parameterName) != jsonObject.end() && jsonObject[parameterName].type() == expectedType;
}

std::unique_ptr<json> LoadJson(std::string jsonPath)
{
	std::ifstream jsonFile(jsonPath.c_str());
	if (jsonFile.peek() == std::ifstream::traits_type::eof())
	{
		Log::GetInstance()->Error("EMPTY SCENE FILE");
		return nullptr;
	}
	std::unique_ptr<json> jsonContent = std::make_unique<json>();
	try
	{
		jsonFile >> *jsonContent;
	}
	catch (json::parse_error& e)
	{
		Log::GetInstance()->Error("THE SCENE FILE IS NOT JSON");
		return nullptr;
	}
	return jsonContent;
}
}