#include <engine/engine.h>
#include <engine/scene.h>

int main()
{
	sfge::Engine engine;
	engine.Init(false, true);
	auto sceneManager = std::dynamic_pointer_cast<sfge::SceneManager>(
		engine.GetModule(sfge::EngineModule::SCENE_MANAGER));
	sceneManager->SetCurrentScene( sceneManager->LoadScene("data/scenes/test.scene"));

	engine.Start();
#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}
