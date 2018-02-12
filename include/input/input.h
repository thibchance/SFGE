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

#ifndef SFGE_INPUT_H
#define SFGE_INPUT_H

#include <engine/engine.h>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

namespace sfge
{
class Keyboard;
/**
* \brief Handles Input like the Keyboard, the Joystick or the Mouse
*/
class InputManager : public Module
{
public:
	using Module::Module;

	InputManager(Engine& engine, bool enable = true);
	/**
	 * \brief Initialize the Input Manager
	 */
	void Init() override;
	/**
	 * \brief Update called each frame to report input status
	 * \param dt Delta time since last frame
	 */
	void Update(sf::Time dt) override;
	void Destroy() override;

	std::shared_ptr<InputManager> GetInputManager();
	std::shared_ptr<Keyboard> GetKeyboard();

private:

protected:
	std::shared_ptr<InputManager> m_InputManager = nullptr;
	std::shared_ptr<Keyboard> m_Keyboard = nullptr;
};

class Keyboard : public Singleton<Keyboard>
{
public:
	bool IsKeyHeld(sf::Keyboard::Key);
	bool IsKeyDown(sf::Keyboard::Key);
	bool IsKeyUp(sf::Keyboard::Key);

private:
	bool keyPressed = false;
};

class Mouse
{
public:
private:

};

class Controller
{
public:
private:

};

}
#endif
