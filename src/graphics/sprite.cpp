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

#include <graphics/graphics.h>
#include <graphics/sprite.h>
#include <utility/file_utility.h>

#include <engine/log.h>

namespace sfge
{
void Sprite::Update(sf::Time dt)
{
}
void Sprite::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}
void Sprite::SetTexture(sf::Texture * newTexture)
{
	sprite.setTexture(*newTexture);
}
void Sprite::SetLayer(int layer)
{
	
}
std::shared_ptr<Sprite> Sprite::LoadSprite(json& componentJson, GameObject& gameObject)
{
	auto graphicsManager = std::dynamic_pointer_cast<GraphicsManager>(
		Engine::GetInstance()->GetModule(sfge::EngineModule::GRAPHICS_MANAGER));
	auto spriteManager = graphicsManager->GetSpriteManager();
	if (spriteManager != nullptr)
	{
		auto newSprite = std::make_shared<Sprite>(gameObject);
		spriteManager->LoadSprite(componentJson, newSprite);
		return newSprite;
	}
	return nullptr;
}
SpriteManager::SpriteManager(GraphicsManager& graphicsManager):Module(), m_GraphicsManager(graphicsManager)
{
}
void SpriteManager::Init()
{
}

void SpriteManager::Update(sf::Time dt)
{
}

void SpriteManager::Destroy()
{
}

void SpriteManager::LoadSprite(json& componentJson, std::shared_ptr<Sprite> newSprite)
{
	if(componentJson.find("path") != componentJson.end())
	{
		std::string path = componentJson["path"].get<std::string>();
		sf::Texture* texture = nullptr;
		if (FileExists(path))
		{
			unsigned int text_id = m_GraphicsManager.GetTextureManager()->LoadTexture(path);
			if (text_id != 0)
			{
				texture = m_GraphicsManager.GetTextureManager()->GetTexture(text_id);
				newSprite->SetTexture(texture);
			}
		}
	}
	else
	{
		Log::GetInstance()->Error("[Error] No Path for Sprite");
	}
	if (componentJson.find("layer") != componentJson.end())
	{
		newSprite->SetLayer(componentJson["layer"]);
	}
}

TextureManager::TextureManager(GraphicsManager & graphicsManager):Module(), m_GraphicsManager(graphicsManager)
{
}

void TextureManager::Init()
{
}

void TextureManager::Update(sf::Time dt)
{
}

void TextureManager::Destroy()
{
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
			return increment_id;
		}
	}
	else
	{
		if (FileExists(filename) && filename != "")
		{
			increment_id++;
			sf::Texture texture;
			if (!texture.loadFromFile(filename))
				return 0U;
			refCountMap[increment_id] = 1;
			nameIdsMap[filename] = increment_id;
			texturesMap[increment_id] = texture;
			return increment_id;
		}
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
