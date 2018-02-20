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
	engine.Init();
	sfge::SoundBuffer buffer;
	json objectJson;
	objectJson["path"] = "C:/Users/guill/Music/Laser.wav";
	json objectJson2;
	objectJson2["path"] = "C:/Users/guill/Music/BasicGun.wav";
	sfge::GameObject gameObject;
	auto sound = dynamic_cast<sfge::Sound*>(sfge::Sound::LoadComponent(engine,objectJson,&gameObject));
	auto sound1 = sound->LoadSound(engine, objectJson,&gameObject);
	auto sound3 = sound->LoadSound(engine, objectJson2, &gameObject);
	auto sound4 = sound->LoadSound(engine, objectJson2, &gameObject);
	//SOUND TEST !!!

	//MUSIC TEST !!!
	sfge::MusicManager musicManager;
	unsigned int musicId = musicManager.LoadMusic("C:/Users/guill/Music/Harry_Potter_Theme_Song_Hedwigs_Theme.ogg");
	std::shared_ptr<sf::Music> musictest = musicManager.GetMusic(musicId);
	//MUSIC TEST !!!
	
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test Audio");
	sf::Time dt;
	// run the program as long as the window is open
	while (window.isOpen())
	{

		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		keyboardManager.Update(dt);
		if (keyboardManager.IsKeyDown(sf::Keyboard::Space))
		{
			std::cout << "play";
			sound1->play();
		}
		if (keyboardManager.IsKeyUp(sf::Keyboard::Q))
		{
			musictest->play();
		}
		if (keyboardManager.IsKeyDown(sf::Keyboard::S))
		{
			sound3->play();
		}
		if (keyboardManager.IsKeyDown(sf::Keyboard::D))
		{
			sound4->play();
		}
		// clear the window with black color
		window.clear(sf::Color::Black);
		// end the current frame
		window.display();
	}

	return 0;
}