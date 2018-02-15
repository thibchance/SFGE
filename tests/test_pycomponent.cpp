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
#include <engine/engine.h>
#include <engine/log.h>
#include <python/python_engine.h>
#include <python/pycomponent.h>
#include <engine/game_object.h>
#include <utility/json_utility.h>
#include <memory>

int main()
{
	sfge::Engine engine;
	engine.Init(true);

	auto pythonManager = std::dynamic_pointer_cast<std::shared_ptr<sfge::PythonManager>>(
			engine.GetModule(sfge::EngineModule::PYTHON_MANAGER));

	sfge::GameObject* gameObject = new sfge::GameObject();
	{
		json componentJson;

		componentJson["type"] = (int)sfge::ComponentType::TRANSFORM;
		sfge::Component::LoadComponent(engine, componentJson, *gameObject);

		componentJson["type"] = (int)sfge::ComponentType::PYCOMPONENT;
		componentJson["script_path"] = "scripts/component_test.py";
		sfge::Component::LoadComponent(engine, componentJson, *gameObject);

		componentJson["script_path"] = "scripts/component_test.py";
		sfge::Component::LoadComponent(engine, componentJson, *gameObject);


		for(int i = 0; i < 10; i++)
		{
			sfge::Log::GetInstance()->Msg("GAME OBJECT UPDATE");
			gameObject->Update(sf::seconds(0.4));
		}
	}
	delete(gameObject);
	engine.Destroy();

#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}
