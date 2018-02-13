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

#include <graphics/texture.h>
#include <engine/log.h>
#include <utility/file_utility.h>

//STL
#include <sstream>


namespace sfge
{

unsigned int TextureManager::LoadTexture(std::string filename)
{
	{
		std::ostringstream oss;
		oss << "Loading texture " << filename;
		Log::GetInstance()->Msg(oss.str());
	}
	if (nameIdsMap.find(filename) != nameIdsMap.end())
	{
		auto text_id = nameIdsMap[filename];
		//Check if the texture was destroyed
		auto checkTexture = texturesMap.find(text_id);
		if (checkTexture != texturesMap.end())
		{
			return nameIdsMap[filename];
		}
		else
		{
			std::shared_ptr<sf::Texture> texture = std::make_shared<sf::Texture>();
			if (!texture->loadFromFile(filename))
				return 0U;
			nameIdsMap[filename] = increment_id;
			texturesMap[increment_id] = texture;
			return increment_id;
		}
	}
	else
	{
		if (FileExists(filename))
		{
			increment_id++;
			auto texture = std::make_shared<sf::Texture>();
			if (!texture->loadFromFile(filename))
				return 0U;
			nameIdsMap[filename] = increment_id;
			texturesMap[increment_id] = texture;
			return increment_id;
		}
	}
	return 0U;
}






std::shared_ptr<sf::Texture> TextureManager::GetTexture(unsigned int text_id)
{
	if (texturesMap.find(text_id) != texturesMap.end())
	{
		return texturesMap[text_id];
	}
	return nullptr;
}

}
