/*
 * test_shape.cpp
 *
 *  Created on: Feb 6, 2018
 *      Author: efarhan
 */
#include <graphics/graphics.h>
#include <graphics/shape.h>
#include <engine/log.h>
#include <engine/game_object.h>
#include <utility/json_utility.h>

int main()
{
	sfge::Engine engine;
	engine.Init(true);

	auto graphicsManager = std::dynamic_pointer_cast<sfge::GraphicsManager>(
			engine.GetModule(sfge::EngineModule::GRAPHICS_MANAGER));

	json gameObjectJson =
	{
			{"name", "ShapeTest"},
			{"components",
					{
							{
									{"type", 3},
									{"shape_type",1},
									{"position", {100,300}},
									{"radius", 500.0}
							},
							{
									{"type", 3},
									{"shape_type",2},
									{"position", {500,300}},
									{"size", {100,100}}
							}
					}
			}
	};


	auto gameObject = sfge::GameObject::LoadGameObject(engine, gameObjectJson);
	// create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Test Shape");


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
		// clear the window with black color
		window.clear(sf::Color::Black);

		graphicsManager->GetShapeManager()->Draw(window);

		// end the current frame
		window.display();
	}
	engine.Destroy();

#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}

