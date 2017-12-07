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

#ifndef SFGE_PYENGINE_H
#define SFGE_PYENGINE_H

#include <engine/engine.h>
#include <engine/component.h>
#include <SFML/System/Time.hpp>
namespace sfge
{
/**
* \brief Manage the python interpreter
*/
class PythonManager : public Module
{
public:
	using Module::Module;
	/**
	* \brief Initialize the python interpreter
	*/
	void Init() override;
	/**
	* \brief Update the python interpreter, called only in play mode
	* \param dt The delta time since last frame
	*/
	void Update(sf::Time dt) override;
	/**
	* \brief Finalize the python interpreter
	*/
	void Destroy() override;
private:

};

class PythonScript : public Component
{
public:
	static PythonScript* LoadPythonScript(json componentJson);
};
}
#endif /* SFGE_PYENGINE_H */
