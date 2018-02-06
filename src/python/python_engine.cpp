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
#include <engine/scene.h>
#include <engine/game_object.h>
#include <engine/component.h>
#include <engine/log.h>
#include <python/python_engine.h>
#include <python/pycomponent.h>
#include <utility/file_utility.h>



PYBIND11_MODULE(SFGE, m)
{
	py::class_<sfge::Scene> scene(m, "Scene");
	py::class_<sfge::GameObject> game_object(m, "GameObject");
	py::class_<sfge::Component, sfge::PyComponent> component(m, "Component");
	component.def(py::init<sfge::GameObject&>());
		component.def("update", &sfge::Component::Update);
}

void sfge::PyComponent::Update(float dt)
{
	PYBIND11_OVERLOAD_PURE(
		void,
		sfge::Component,
		Update,
		dt
	);
}
namespace sfge
{





void PythonManager::Init()
{
	Log::GetInstance()->Msg("Initialise the python embed interpretor");
	py::initialize_interpreter();
}

void PythonManager::Update(sf::Time)
{
}


void PythonManager::Destroy()
{
	py::finalize_interpreter();
}

unsigned int PythonManager::LoadPyComponentFile(std::string script_path)
{


	fs::path p = script_path;
	if(fs::is_regular_file(p))
	{
		if(pythonScriptMap.find(script_path) != pythonScriptMap.end())
		{
			unsigned int scriptId = pythonScriptMap[script_path];
			if(scriptId == 0U)
			{
				std::ostringstream oss;
				oss << "Python script: "<<script_path<<" has id 0";
				Log::GetInstance()->Error(oss.str());
				return 0U;
			}
			{
				return scriptId;
			}
		}
		else
		{
			try
			{
				std::string module_name = p.filename().replace_extension("");
				std::string class_name = module2class(module_name);
				py::object globals  = py::globals();
				py::object module   = import(module_name, script_path, globals);
				{
					std::stringstream oss;
					oss << "Module imported: "<< py::str(module).cast<std::string>();
					Log::GetInstance()->Msg(oss.str());
				}

				py::object componentClass = module.attr(class_name.c_str());
				incrementalScriptId++;
				pythonScriptMap[script_path] = incrementalScriptId;
				pythonObjectMap[incrementalScriptId] = componentClass;
				return incrementalScriptId;
			}
			catch(const py::error_already_set& e)
			{
				std::stringstream oss;
				oss << "Python error on script file: "<<script_path<<"\n"<<e.what();
				Log::GetInstance()->Error(oss.str());
			}
		}
	}
	else
	{
		std::stringstream oss;
		oss << "Python error on script file: "<<script_path<<" is not a file!\n";
		Log::GetInstance()->Error(oss.str());
	}

	return 0U;
}

py::object PythonManager::GetPyComponent(unsigned int scriptId)
{
	if(pythonObjectMap.find(scriptId) != pythonObjectMap.end())
	{
		return pythonObjectMap[scriptId];
	}
	return py::none();
}



}
