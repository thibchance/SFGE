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
#include <graphics/texture.h>
#include <utility/file_utility.h>

#include <engine/log.h>
#include <engine/transform.h>

namespace sfge
{
void Sprite::Update(float dt)
{
}
void Sprite::Draw(sf::RenderWindow& window)
{
	sprite.setPosition(gameObject.GetTransform()->GetPosition());
	sprite.setScale(gameObject.GetTransform()->GetScale());
	sprite.setRotation(gameObject.GetTransform()->GetEulerAngle());
	window.draw(sprite);
}
void Sprite::SetTexture(std::shared_ptr<sf::Texture> newTexture)
{
	sprite.setTexture(*newTexture);
}
void Sprite::SetLayer(int layer)
{
	
}
bool Sprite::SpriteLayerComp(std::shared_ptr<Sprite> s1, std::shared_ptr<Sprite> s2)
{
	return s1->layer>s2->layer;
}
std::shared_ptr<Sprite> Sprite::LoadSprite(Engine& engine, json& componentJson, GameObject& gameObject)
{
	auto graphicsManager = std::dynamic_pointer_cast<GraphicsManager>(
		engine.GetModule(sfge::EngineModule::GRAPHICS_MANAGER));
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
SpriteManager::SpriteManager(GraphicsManager& graphicsManager): m_GraphicsManager(graphicsManager)
{
}

void SpriteManager::Update(sf::Time dt)
{
	m_Sprites.sort(Sprite::SpriteLayerComp);
}

void SpriteManager::Draw(sf::RenderWindow& window)
{
	for (auto sprite : m_Sprites)
	{
		sprite->Draw(window);
	}
}

void SpriteManager::LoadSprite(json& componentJson, std::shared_ptr<Sprite> newSprite)
{
	if (newSprite == nullptr)
		return;
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
		else
		{
			std::ostringstream oss;
			oss << "Texture file " << path << " does not exist";
			Log::GetInstance()->Error(oss.str());
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
	m_Sprites.push_back(newSprite);
}







}
