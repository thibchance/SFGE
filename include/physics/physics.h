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

#ifndef SFGE_PHYSICS_H
#define SFGE_PHYSICS_H

#include <Box2D/Box2D.h>
#include <SFML/System/Time.hpp>

#include <engine/engine.h>
#include <engine/component.h>



/**
 * \brief The Physics Manager use Box2D to simulate 2D physics
 */
class PhysicManager : public Module<PhysicManager>
{
public:
	/**
	 * \brief Initialize the Physics Manager, but do not create a b2World
	 */
    void Init() override;
    /**
     * \brief Initialize a b2World
     */
    void InitWorld();
    /**
     * \brief Create Rigidbody
     * \return A 2D Rigidbody
     */
    b2Body* CreateBody();
    /**
     * \brief Destroy the body from the b2World
     * \param body Rigidbody to be destroyed
     */
    void DestroyBody(b2Body* body);
    /**
     * \brief Destroy the current b2World
     */
    void DestroyWorld();
    /**
     * \brief Called each frame to update the b2World if not in editor mode
     * @param dt Delta time since last frame
     */
	void Update(sf::Time dt) override;
	/**
	* \brief Called at the end of the program to Destroy a b2World, if it sill exists
	*/
	void Destroy() override;
private:
    b2World* m_World = nullptr;
    ~PhysicManager();

};

class Rigidbody : public Component
{
protected:
	b2Body* m_Body = nullptr;
};


#endif
