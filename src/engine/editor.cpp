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

#include <imgui.h>
#include <imgui-SFML.h>

#include <engine/editor.h>
#include <graphics/graphics.h>
#include <engine/scene.h>
#include <engine/game_object.h>
#include <engine/log.h>


namespace sfge
{
/**
* \brief Initialize the SceneManager, get the Configuration from Engine and save the Scene lists from it
*/
void Editor::Init()
{
	m_GraphicsManager = std::dynamic_pointer_cast<GraphicsManager>(
		Engine::GetInstance()->GetModule(EngineModule::GRAPHICS_MANAGER));
	m_SceneManager = std::dynamic_pointer_cast<SceneManager>(Engine::GetInstance()->GetModule(EngineModule::SCENE_MANAGER));
	if (m_Enable)
	{
		ImGui::SFML::Init(*m_GraphicsManager->GetWindow(), true);
	}
}
void Editor::Update(sf::Time dt)
{
	if (m_Enable)
	{
		ImGui::SFML::Update(*m_GraphicsManager->GetWindow(), dt);

		ImGui::Begin("GameObjects");
		if (m_SceneManager->GetCurrentScene() != nullptr)
		{
			for (auto gameObject : m_SceneManager->GetCurrentScene()->GetGameObjects())
			{
				ImGui::Selectable(gameObject->GetName().c_str());
			}
		}
		else
		{
			Log::GetInstance()->Error("No Current Scene for editor");
		}
		ImGui::End();

		
	}
}
/**
* \brief Update the SceneManager, mostly updating the GameObjects of the current Scene and doing the transition when needed
* \param dt Delta time since last frame
*/
void Editor::ProcessEvent(sf::Event& event)
{
	if (m_Enable)
	{
		ImGui::SFML::ProcessEvent(event);
	}
}

void Editor::Draw()
{
	ImGui::SFML::Render(*m_GraphicsManager->GetWindow());
}



/**
* \brief Finalize and delete everything created in the SceneManager
*/
void Editor::Destroy()
{
	if (m_Enable)
	{
		m_GraphicsManager = nullptr;
		ImGui::Shutdown();
	}
}
}