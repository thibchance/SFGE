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
#include <audio/audio.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <engine/engine.h>
#include <engine/log.h>
#include <input/input.h>


int main()
{
	sfge::KeyboardManager keyboardManager;

	//SOUND TEST !!!
	sfge::Engine engine;
	engine.Init(true);
	json gameObjectJson;

	json objectJson;
	objectJson["path"] = "data/audio/sounds/Laser.wav";
	objectJson["type"] = (int)sfge::ComponentType::SOUND;

	gameObjectJson["components"] = json::array({ objectJson });
	gameObjectJson["name"] = "AudioGameObject";

	sfge::GameObject* gameObject = sfge::GameObject::LoadGameObject(engine, gameObjectJson);

	auto sound = gameObject->GetComponent<sfge::Sound>();
	//SOUND TEST !!!

	//MUSIC TEST !!!
	sfge::MusicManager musicManager;
	auto goodMusic = musicManager.GetMusic(musicManager.LoadMusic("data/audio/musics/Harry_Potter_Theme_Song_Hedwigs_Theme.ogg"));
	//MUSIC TEST !!!
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test Audio");
	sf::Clock clock;
	// run the program as long as the window is open
	while (window.isOpen())
	{
		sf::Time dt = clock.restart();
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		gameObject->Update(dt);
		keyboardManager.Update(dt);
		if (keyboardManager.IsKeyDown(sf::Keyboard::Space))
		{
			sfge::Log::GetInstance()->Msg("PLAY SOUND");
			sound->Play();
		}
		if (keyboardManager.IsKeyUp(sf::Keyboard::Q))
		{
			goodMusic->play();
		}
		// clear the window with black color
		window.clear(sf::Color::Black);
		// end the current frame
		window.display();
	}
	engine.Destroy();
#if WIN32
	system("pause");
#endif
	return 0;
}