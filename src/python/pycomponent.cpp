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


#include <python/pycomponent.h>
#include <python/python_engine.h>
#include <engine/log.h>

namespace sfge
{

void PyComponent::Update(float dt)
{
	PYBIND11_OVERLOAD_PURE_NAME(
		void,
		Component,
		"update",
		Update,
		dt
	);
}

PyComponent::~PyComponent()
{
	Log::GetInstance()->Msg("Destroying PyComponent");
}

void PyComponent::SetInstance(py::object& instance)
{
	m_Instance = instance;
}

std::shared_ptr<PyComponent> PyComponent::LoadPythonScript(Engine& engine, json& componentJson, GameObject& gameObject)
{
	auto pythonManager = std::dynamic_pointer_cast<PythonManager>(engine.GetModule(EngineModule::PYTHON_MANAGER));
	if(CheckJsonParameter(componentJson, "script_path", json::value_t::string))
	{
		unsigned int scriptId = pythonManager->LoadPyComponentFile(componentJson["script_path"]);
		if(scriptId != 0U)
		{
			auto classComponent = pythonManager->GetPyComponent(scriptId);
			auto componentInstance = classComponent(gameObject);
			//componentInstance.attr("update")(0.2f);
			auto pyComponent = std::shared_ptr<PyComponent>(componentInstance.cast<PyComponent*>());
			pyComponent->SetInstance(componentInstance);
			return pyComponent;
		}
	}
	return nullptr;
}

}
