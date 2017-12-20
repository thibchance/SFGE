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
	sprite.setPosition(gameObject.GetTransform()->GetPosition());
	window.draw(sprite);
}
void Sprite::SetTexture(std::shared_ptr<sf::Texture> newTexture)
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
		//To Ensure that we have a transform
		gameObject.GetTransform();
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
	if(CheckJsonParameter(componentJson, "path", json::value_t::string))
	{
		std::string path = componentJson["path"].get<std::string>();
		std::shared_ptr<sf::Texture> texture = nullptr;
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
	if (CheckJsonParameter(componentJson, "layer", json::value_t::number_integer))
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
