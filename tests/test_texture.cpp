#include <graphics/sprite.h>
#include <graphics/texture.h>
#include <engine/log.h>
int main()
{
	sfge::TextureManager textureManager;

	unsigned int goodTextId = textureManager.LoadTexture("C:/Users/guill/Pictures/DOOOOOOOOOOOOOOOOOOOOOOOOOOOM.jpg");
	unsigned int badTextId = textureManager.LoadTexture("prout.jpg");

	sf::Sprite sprite;
	if (badTextId != 0)
	{
		sfge::Log::GetInstance()->Msg("Loading Bad File");
		sprite.setTexture(*textureManager.GetTexture(badTextId));
	}
	if (goodTextId != 0)
	{

		sfge::Log::GetInstance()->Msg("Loading Good File");
		sprite.setTexture(*textureManager.GetTexture(goodTextId));
	}

	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test Sprite");

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

		// clear the window with black color
		window.clear(sf::Color::Black);

		window.draw(sprite);

		// end the current frame
		window.display();
	}
#if WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}
