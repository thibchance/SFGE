#include <engine/engine.h>
#include <python/python_engine.h>
#include <python/pycomponent.h>
#include <utility/json_utility.h>
#include <memory>

int main()
{
	sfge::Engine engine;
	engine.Init(true);

	auto pythonManager = std::dynamic_pointer_cast<std::shared_ptr<sfge::PythonManager>>(
			engine.GetModule(sfge::EngineModule::PYTHON_MANAGER));
	{
		sfge::GameObject gameObject;
		json componentJson;
		componentJson["script_path"] = "scripts/component_test.py";
		auto pyComponent = sfge::PyComponent::LoadPythonScript(engine, componentJson, gameObject);
		if(pyComponent != nullptr)
		{
			pyComponent->Update(0.3f);
		}
	}
	engine.Destroy();
	return EXIT_SUCCESS;
}
