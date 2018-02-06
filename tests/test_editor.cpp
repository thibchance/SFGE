#include <engine/engine.h>
#include <engine/scene.h>

int main()
{
	sfge::Engine::GetInstance()->Init(false, true);
	auto sceneManager = std::dynamic_pointer_cast<sfge::SceneManager>(
		sfge::Engine::GetInstance()->GetModule(sfge::EngineModule::SCENE_MANAGER));
	sceneManager->SetCurrentScene( sceneManager->LoadScene("data/scenes/test.scene"));
	sfge::Engine::GetInstance()->Start();

	sfge::Engine::GetInstance()->Destroy();
#ifdef WIN32
	system("pause");
#endif
	return EXIT_SUCCESS;
}
