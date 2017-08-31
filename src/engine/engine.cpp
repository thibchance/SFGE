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

#include <engine/engine.h>
#include <python/python_engine.h>

#include <sstream>

Engine::Engine(): window(NULL), running(false)
{
    
}

Engine::~Engine()
{
	delete window;
	window = NULL;
}

void Engine::init()
{
    init_python();
	window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFGE 0.1");
	init_gui();
	checkVersion();
	
	running = true;

}

void Engine::start()
{
	sf::Clock clock;
	while (running)
	{
		sf::Time dt = clock.restart();
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window->close();
				running = false;
			}
		}
		
		window->clear();
		ImGui::SFML::Update(*window, dt);
		window->display();
	}
}

void Engine::checkVersion()
{
    
    sf::ContextSettings settings = window->getSettings();
    std::stringstream log_message;
    log_message << "OpenGL version:"<< settings.majorVersion << "." << settings.minorVersion << std::endl;
    Log::getInstance()->msg(log_message.str().c_str());
}

void Engine::init_gui()
{
	ImGui::SFML::Init(*(sf::RenderTarget*)window);
}

