/*
MIT License

Copyright (c) 2017 Elias Farhan

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

#include <input/input.h>
#include <engine/log.h>
#include <SFML/Window.hpp>
#include <imgui-SFML.h>
#include <imgui.h>

void InputManager::init()
{
	window = Engine::getWindow();
}

void InputManager::update(sf::Time dt)
{
	manageEvent();
}

void InputManager::manageEvent()
{
	sf::Event event;
	if (window == NULL)
	{
		Log::getInstance()->error("WINDOW IS NULL IN INPUT MANAGER");
		return;
	}
	while (window->pollEvent(event))
	{
		ImGui::SFML::ProcessEvent(event);
		if (event.type == sf::Event::Closed)
		{
			Engine::getInstance()->running = false;
			window->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::E)
			{

			}
		}
	}
}
