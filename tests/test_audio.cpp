#include <audio/audio.h>
#include <iostream>
#include<SFML/Graphics.hpp>
#include <engine/engine.h>
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
			std::cout << "play";
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

	return 0;
}