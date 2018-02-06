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

#ifndef SFGE_SHAPE_H_
#define SFGE_SHAPE_H_

#include <engine/engine.h>
#include <engine/component.h>
#include <utility/json_utility.h>

//Externals
#include <SFML/Graphics.hpp>

namespace sfge
{

enum class ShapeType
{
	NONE,
	CIRCLE,
	RECTANGLE,
	POLYGON,
	CONVEX,
};

class Shape : public Component
{
public:
	Shape(GameObject& gameObject, sf::Vector2f position);

	void Update(float time) override;
	void Draw(sf::RenderWindow& window);
	static std::shared_ptr<Shape> LoadShape(Engine& engine, json& componentJson, GameObject& gameObject);
protected:
	sf::Vector2f m_Position;
	std::shared_ptr<sf::Shape> m_Shape = nullptr;
};

class Circle : public Shape
{
public:
	Circle(GameObject& gameObject, sf::Vector2f position, float radius);
	static std::shared_ptr<Circle> LoadCircle(json& componentJson, GameObject& gameObject, sf::Vector2f position);
protected:
	float m_Radius;
};

class Rectangle : public Shape
{
public:
	Rectangle(GameObject& gameObject, sf::Vector2f position, sf::Vector2f size);

	static std::shared_ptr<Rectangle> LoadRectangle(json& componentJson, GameObject& gameObject, sf::Vector2f position);
protected:
	sf::Vector2f m_Size;

};

class ShapeManager
{

public:
	ShapeManager(GraphicsManager& graphicsManager);
	void AddShape(std::shared_ptr<Shape> shape);
	void Draw(sf::RenderWindow& window);
protected:
	std::list<std::shared_ptr<Shape>> m_Shapes;
	GraphicsManager& m_GraphicsManager;
};

}
#endif /* SRC_GRAPHICS_SHAPE_H_ */
