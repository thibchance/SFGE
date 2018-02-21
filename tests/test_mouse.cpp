#include <engine/engine.h>
#include <SFML/Graphics.hpp>
#include <input/input.h>
#include <iostream>
#include <engine/log.h>
#include <sstream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Test Mouse");
	sf::Font font;
	if (font.loadFromFile("data/font/CHEESEBU.TTF"))
	{
		std::cout << "font load";
	}
	sf::Text mouseText;
	mouseText.setFont(font);
	mouseText.setCharacterSize(60);
	mouseText.setColor(sf::Color::Red);
	mouseText.setStyle(sf::Text::Bold);
	mouseText.setPosition(50, 100);
	sf::Mouse mouse;
	
	std::ostringstream oss;
	
	sfge::MouseManager mouseManager;
	sfge::KeyboardManager keyboardManager;
	sf::Time dt;
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;

		oss << " Mouse Position is " << mouseManager.localPosition(window).x << " , " << mouseManager.localPosition(window).y;
		std::string mousePos = oss.str();
		mouseText.setString(mousePos);
		oss.str("");
		oss.clear();

		keyboardManager.Update(dt);
		mouseManager.Update(dt);
		if (keyboardManager.IsKeyDown(sf::Keyboard::Space))
		{
			std::cout << " is key down ";
		}
		if (mouseManager.IsButtonDown(sf::Mouse::Left))
		{
			std::cout << " is button down ";
		}
		if (mouseManager.IsButtonUp(sf::Mouse::Middle))
		{
			std::cout << " is button up ";
		}
		if (mouseManager.IsButtonHeld(sf::Mouse::Left))
		{
			std::cout << " is button held ";
		}
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}
		// clear the window with black color
		window.clear(sf::Color::Black);
		window.draw(mouseText);
		// end the current frame
		window.display();
	}
	system("pause");
	return 0;
}
