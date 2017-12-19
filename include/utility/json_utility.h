#ifndef SFGE_JSON_UTILIY_H
#define SFGE_JSON_UTILIY_H
//Externals includes
#include "json.hpp"
using json = nlohmann::json;
namespace sfge
{

	std::unique_ptr<json> LoadJson(std::string jsonPath);
}
#endif