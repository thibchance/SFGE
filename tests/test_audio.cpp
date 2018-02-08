#include <audio/audio.h>
#include <iostream>
#include<SFML/Graphics.hpp>
#include <engine/engine.h>

int main()
{
	//SOUND BUFFER TEST !!!
	/*sf::Sound sound;
	sfge::SoundBuffer buffer;
	auto soundID = buffer.LoadSoundBuffer("C:/Users/guill/Music/Laser.wav");
	sound.setBuffer(*buffer.GetSoundBuffer(soundID));*/
	//SOUND BUFFER TEST !!!

	//SOUND TEST !!!
	/*sfge::Engine* engine = sfge::Engine::GetInstance();
	engine->Init(true);
	sfge::Sound sound;
	json objectJson;
	objectJson["path"] = "C:/Users/guill/Music/Laser.wav";
	auto sound1 = sound.GetInstance()->LoadSound(objectJson);*/
	//SOUND TEST !!!

	//MUSIC TEST !!!
	sfge::MusicManager musicManager;
	auto goodMusic = musicManager.GetMusic(musicManager.LoadMusic("C:/Users/guill/Music/Harry_Potter_Theme_Song_Hedwigs_Theme.ogg"));
	goodMusic->play();
	//MUSIC TEST !!!

	sf::RenderWindow window(sf::VideoMode(800, 600), "Test Audio");
	// run the program as long as the window is open
	while (window.isOpen())
	{
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			//sound1->play();
		}
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// clear the window with black color
		window.clear(sf::Color::Black);
		// end the current frame
		window.display();
	}
	system("Pause");
}