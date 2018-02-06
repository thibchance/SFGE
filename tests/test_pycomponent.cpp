#include <engine/engine.h>
#include <engine/log.h>
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
			try
			{
				pyComponent->Update(0.4f);
			}
			catch (std::runtime_error& e)
			{
				sfge::Log::GetInstance()->Error(e.what());
			}
		}
		else
		{
			sfge::Log::GetInstance()->Error("Component is null");
		}
	}
	engine.Destroy();
	return EXIT_SUCCESS;
}
