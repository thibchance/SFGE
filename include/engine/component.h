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

#ifndef SFGE_COMPONENT_H
#define SFGE_COMPONENT_H
//Externals includes
#include <SFML/System.hpp>
#include <engine/game_object.h>

namespace sfge
{
class Transform;
/**
 * \brief A GameObject Component that can be anything
 */
class Component
{
public:
	/**
	 * \brief Constructor of Component takes the parent GameObject as reference
	 * \param parentGameObject The parent GameObject
	 */
	Component(GameObject& parentGameObject);
	/**
	* \brief Update the Component
	* \param dt Delta time since last frame
	*/
	virtual void Update(sf::Time dt) = 0;

protected:
	GameObject& gameObject;
	Transform* transform = nullptr;

};

class Transform : public Component
{
public:
	/**
	 * \brief Constructor of Transform takes the parent GameObject as reference
	 * \param parentGameObject
	 */
	Transform(GameObject& parentGameObject);

	static Transform* LoadTransform(json componentJson);

	void Update(sf::Time dt) override;

	float GetEulerAngle();
	void SetEulerAngle(float eulerAngle);
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetScale();
	void SetScale(sf::Vector2f scale);

private:
	sf::Vector2f position;
	sf::Vector2f scale;
	float eulerAngle;

};
}
#endif
