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

#include <python/python_engine.h>
#include <pybind11/embed.h>// everything needed for embedding
namespace py = pybind11;

namespace sfge
{

/**
 * \brief Python abstraction of Component
 */
class PyComponent : public Component
{
public:
	using Component::Component;

	void Update(float dt) override
	{
		PYBIND11_OVERLOAD(
			void,
			Component,
			Update,
			dt
		);
	}

	static std::shared_ptr<PyComponent> LoadPythonScript(json& componentJson, GameObject& gameObject);
};

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

	/**
	 * \brief Load a python script and return a python object of it
	 * \param script_name
	 * \return scriptId
	 */
	unsigned int LoadPyComponentFile(std::string script_name);
	/**
	 * \brief Get a python component object
	 * \param scriptId
	 * \return python object of the python component class
	 */
	py::object GetPyComponent(unsigned int scriptId);
private:
	std::map<std::string, unsigned int> pythonScriptMap;
	std::map<unsigned int, py::object> pythonObjectMap;
	unsigned int incrementalScriptId = 0;
};

}
#endif /* SFGE_PYENGINE_H */
