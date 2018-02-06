#include <engine/engine.h>
#include <python/python_engine.h>
#include <utility/json_utility.h>
#include <utility/python_utility.h>
#include <memory>

int main()
{
	sfge::Engine::GetInstance()->Init(true);

	auto pythonManager = std::dynamic_pointer_cast<std::shared_ptr<sfge::PythonManager>>(
			sfge::Engine::GetInstance()->GetModule(sfge::EngineModule::PYTHON_MANAGER));
	{
		sfge::GameObject gameObject;
		json componentJson;
		componentJson["script_path"] = "scripts/component_test.py";
		auto pyComponent = sfge::PyComponent::LoadPythonScript(componentJson, gameObject);
		if(pyComponent != nullptr)
		{
			pyComponent->Update(0.3f);
		}
	}
	sfge::Engine::GetInstance()->Destroy();
	return EXIT_SUCCESS;
}
