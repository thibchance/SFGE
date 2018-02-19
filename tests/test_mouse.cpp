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
	if (font.loadFromFile("C:/Users/guill/OneDrive/Documents/CHEESEBU.TTF"))
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
	
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		oss << " Mouse Position is " << mouse.getPosition().x << " , " << mouse.getPosition().y;
		mouseText.setString(oss.str());

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
