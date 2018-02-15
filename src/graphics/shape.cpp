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

#include <graphics/graphics.h>
#include <graphics/shape.h>
#include <utility/json_utility.h>
#include <engine/log.h>

namespace sfge
{

Shape::Shape(GameObject& gameObject, sf::Vector2f position):
		Component(gameObject)
{

}

void Shape::Update(float time)
{
}

void Shape::Draw(sf::RenderWindow& window)
{
	if(m_Shape != nullptr)
	{
		window.draw(*m_Shape);
	}
}

void Shape::Init()
{
}

Shape* Shape::LoadShape(Engine& engine, json& componentJson, GameObject& gameObject)
{
	Shape* shape = nullptr;
	sf::Vector2f position;
	if(CheckJsonParameter(componentJson, "position", json::value_t::array))
	{
		if(componentJson["position"].size() == 2)
		{
			position = sf::Vector2f(componentJson["position"][0], componentJson["position"][1]);
		}
	}

	if(CheckJsonParameter(componentJson, "shape_type", json::value_t::number_integer))
	{
		ShapeType shapeType = (ShapeType)componentJson["shape_type"];
		switch(shapeType)
		{
		case ShapeType::CIRCLE:
			shape = Circle::LoadCircle(componentJson, gameObject, position);
			break;
		case ShapeType::RECTANGLE:
			shape = Rectangle::LoadRectangle(componentJson, gameObject, position);
			break;

		}
	}
	if(shape != nullptr)
	{
		{
			Log::GetInstance()->Msg("Load shape");
		}
		auto graphicsManager = std::dynamic_pointer_cast<GraphicsManager>(
				engine.GetModule(EngineModule::GRAPHICS_MANAGER));
		graphicsManager->GetShapeManager()->AddShape(shape);
	}
	return shape;
}

Circle::Circle(GameObject& gameObject, sf::Vector2f position, float radius):
		Shape(gameObject, position)
{
	m_Radius = radius;
	m_Shape = std::make_shared<sf::CircleShape>(radius);
	m_Shape->setFillColor(sf::Color::Green);
	m_Shape->setPosition(position);
}


Circle* Circle::LoadCircle(json& componentJson, GameObject& gameObject, sf::Vector2f position)
{
	float radius = 1.0f;

	if(CheckJsonParameter(componentJson, "radius", json::value_t::number_float))
	{
		radius = componentJson["radius"];
	}

	return new Circle(gameObject, position, radius);

}
Rectangle::Rectangle(GameObject& gameObject, sf::Vector2f position, sf::Vector2f size):
		Shape(gameObject, position)
{
	m_Size = size;
	m_Shape = std::make_shared<sf::RectangleShape>(size);
	m_Shape->setFillColor(sf::Color::Red);
	m_Shape->setPosition(position);
}

Rectangle* Rectangle::LoadRectangle(json& componentJson, GameObject& gameObject, sf::Vector2f position)
{

	sf::Vector2f size;
	if(CheckJsonParameter(componentJson, "size", json::value_t::array))
	{
		if(componentJson["size"].size() == 2)
		{
			size = sf::Vector2f(componentJson["size"][0], componentJson["size"][1]);
		}
	}
	return new Rectangle(gameObject, position, size);
}


ShapeManager::ShapeManager(GraphicsManager& graphicsManager):
		m_GraphicsManager(graphicsManager)
{

}


void ShapeManager::Draw(sf::RenderWindow& window)
{
	for(auto shape : m_Shapes)
	{
		shape->Draw(window);
	}
}

void ShapeManager::AddShape(Shape* shape)
{
	m_Shapes.push_back(shape);
}


}
