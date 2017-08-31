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


Engine::Engine(): window(NULL), running(false), editor(false), test(false)
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
	window->setFramerateLimit(60);
	initGui();
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
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
			{
				window->close();
				running = false;
			}
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::E)
				{
					editor = !editor;
				}
			}
		}

		ImGui::SFML::Update(*window, dt);
		window->clear();
		if (editor)
			showEditor();
		if (test)
			showTest();
		ImGui::SFML::Render(*window);
		window->display();
	}
	ImGui::SFML::Shutdown();
}

void Engine::checkVersion()
{
    
    sf::ContextSettings settings = window->getSettings();
    std::stringstream log_message;
    log_message << "OpenGL version:"<< settings.majorVersion << "." << settings.minorVersion << std::endl;
    Log::getInstance()->msg(log_message.str().c_str());
}

void Engine::initGui()
{
	ImGui::SFML::Init(*(sf::RenderTarget*)window);
}

void Engine::initTest()
{
	test = true;
}

void Engine::showEditor()
{
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	
	ImGui::Begin("Editor", &editor);
	ImGui::Text("Hello");
	ImGui::End();
}

void Engine::showTest()
{
	ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_FirstUseEver);
	ImGui::Begin("Testbed", &test);
	ImGui::Text("Hello");
	ImGui::End();
}