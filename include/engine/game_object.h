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


#ifndef SFGE_GAMEOBJECT_H
#define SFGE_GAMEOBJECT_H
//External includes
#include "json.hpp"
using json = nlohmann::json;
#include <SFML/System.hpp>
//STL includes
#include <list>
#include <string>

namespace sfge
{

class Component;

/**
* \brief The basic Game Object handler containing a list of Components
*/
class GameObject
{
public:
	/**
	* \brief Update the GameObject and its Components
	* \param dt Delta time since last frame
	*/
	void Update(sf::Time dt);
	/**
	* \brief Load a GameObject and create all its Component
	* \param gameObjectJson the sub json associated with the Game Object
	* \return the heap GameObject that will need to be destroyed
	*/
	static GameObject* LoadGameObject(json gameObjectJson);
protected:
	std::list<Component*> m_Components;
	std::string name;
};
}
#endif
