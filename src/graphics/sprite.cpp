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

#include <graphics/sprite.h>

namespace sfge
{

Sprite* Sprite::LoadSprite(json componentJson)
{
	return nullptr;
}

unsigned int TextureManager::LoadTexture(std::string filename)
{
	if (nameIdsMap.find(filename) != nameIdsMap.end())
	{
		auto text_id = nameIdsMap[filename];
		//Check if the texture was destroyed
		auto checkTexture = texturesMap.find(text_id);
		if (checkTexture != texturesMap.end())
		{
			refCountMap[nameIdsMap[filename]]++;
			return nameIdsMap[filename];
		}
		else
		{
			sf::Texture texture;
			if (!texture.loadFromFile(filename))
				return 0U;
			refCountMap[increment_id] = 1;
			nameIdsMap[filename] = increment_id;
			texturesMap[increment_id] = texture;
		}
	}
	else
	{
		increment_id++;
		sf::Texture texture;
		if (!texture.loadFromFile(filename))
			return 0U;
		refCountMap[increment_id] = 1;
		nameIdsMap[filename] = increment_id;
		texturesMap[increment_id] = texture;
	}
	return 0U;
}





void TextureManager::UnloadTexture(unsigned int text_id)
{
	auto checkRefCount = refCountMap.find(text_id);
	if (checkRefCount != refCountMap.end())
	{
		refCountMap[text_id]--;
		if (refCountMap[text_id] == 0)
		{
			//TODO: unload texture from text_id
			refCountMap.erase(text_id);
			texturesMap.erase(text_id);
		}
	}
}

sf::Texture* TextureManager::GetTexture(unsigned int text_id)
{
	if (texturesMap.find(text_id) != texturesMap.end())
	{
		return &texturesMap[text_id];
	}
	return nullptr;
}

}
