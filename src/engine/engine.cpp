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

#include <engine/engine.h>
#include <engine/scene.h>
#include <graphics/graphics.h>
#include <input/input.h>
#include <python/python_engine.h>

#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>




void Engine::Init()
{
	GraphicsManager::GetInstance()->Init();
	PythonManager::GetInstance()->Init();
	InputManager::GetInstance()->Init();
	SceneManager::GetInstance()->Init();
	
	running = true;

}

void Engine::Start()
{
	sf::Clock clock;
	while (running)
	{
		sf::Time dt = clock.restart();

		InputManager::GetInstance()->Update(dt);
		GraphicsManager::GetInstance()->Update(dt);
	}
	
}

void Engine::InitTest()
{
	test = true;
}

sf::RenderWindow * Engine::GetWindow()
{
	return GraphicsManager::GetInstance()->GetWindow();
}
