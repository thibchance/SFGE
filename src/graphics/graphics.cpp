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
#include <engine/log.h>
#include <engine/config.h>

//Dependencies includes
#include <SFML/Graphics/RenderWindow.hpp>
#include "imgui-SFML.h"
#include "imgui.h"

#include <sstream>

namespace sfge
{
GraphicsManager::GraphicsManager(bool windowless) : Module(), m_Windowless(windowless)
{
	
}
	void GraphicsManager::Init()
{
	auto config = Engine::GetInstance()->GetConfig();
	if (config == nullptr)
	{
		Log::GetInstance()->Error("[Error] Config is null from Graphics Manager");
	}
	if (!m_Windowless && config != nullptr)
	{
		m_Window = std::make_shared<sf::RenderWindow>(
			sf::VideoMode(config->screenResolution.x, config->screenResolution.y),
			"SFGE 0.1");
		if (config->maxFramerate)
		{
			m_Window->setFramerateLimit(config->maxFramerate);
			CheckVersion();
			//Init GUI
			ImGui::SFML::Init((sf::RenderTarget&)(*m_Window));
		}
	}
	
	

	//Init Texture and Sprite Manager
	m_TextureManager = std::make_shared<TextureManager>(*this);
	m_SpriteManager = std::make_shared<SpriteManager>(*this);
}

void GraphicsManager::Update(sf::Time dt)
{
	if (!m_Windowless)
	{
		ImGui::SFML::Update(*m_Window, dt);

		m_Window->clear();

		m_TextureManager->Update(dt);
		m_SpriteManager->Update(dt);

		ImGui::SFML::Render(*m_Window);
		m_Window->display();
	}
}

std::shared_ptr<sf::RenderWindow> GraphicsManager::GetWindow()
{
	return m_Window;
}

std::shared_ptr<SpriteManager> GraphicsManager::GetSpriteManager()
{
	return m_SpriteManager;
}

std::shared_ptr<TextureManager> GraphicsManager::GetTextureManager()
{
	return m_TextureManager;
}

void GraphicsManager::CheckVersion()
{
	sf::ContextSettings settings = m_Window->getSettings();
	std::stringstream log_message;
	log_message << "OpenGL version: " << settings.majorVersion << "." << settings.minorVersion << std::endl;

	Log::GetInstance()->Msg(log_message.str());
}

void checkVersion()
{

}


void GraphicsManager::Destroy()
{
	
	ImGui::SFML::Shutdown();
}

}