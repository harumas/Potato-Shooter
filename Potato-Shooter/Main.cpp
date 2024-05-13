#include "GameScene.h"

void register_scenes(SceneHandler& scene_handler);
void register_services(ServiceLocator& locator);

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC)
{
	ServiceLocator locator;
	SceneHandler scene_handler;

	SetWindowIconID(107);
	SetMainWindowText("Potato Shooter");

	if (App::initialize() == -1)
	{
		return -1;
	}

	register_services(locator);
	register_scenes(scene_handler);

	scene_handler.load_all(locator);

	Scene* current = scene_handler.switch_to(1);
	shared_ptr<Time> timer = locator.resolve<Time>();
	shared_ptr<Device> device = locator.resolve<Device>();
	shared_ptr<Cursor> cursor = locator.resolve<Cursor>();

	while (App::refresh_frame() == 0)
	{
		if (!current->initialized)
		{
			timer->init();
			current->init();
		}

		timer->update();
		device->update();
		cursor->update();
		GUIUpdater::update();
		int scene_id = current->update();

		if (scene_id == 0)
		{
			current->draw();
			GUIUpdater::draw();
		}
		else if (scene_id > 0)
		{
			current->clear();
			current = scene_handler.switch_to(scene_id);
		}
		else break; //マイナスのときは終了
	}

	App::finalize();

	return 0;
}

//依存関係を登録
void register_services(ServiceLocator& locator)
{
	locator.register_type<ResourceHandler>();
	locator.register_type<Cursor>();
	locator.register_type<CollisionSimulator>();
	locator.register_type<Device>();
	locator.register_type<GameScore>();
	locator.register_type<Time>();

	GUIUpdater::set_service(locator);

	Player* player = new Player(locator);
	locator.register_instance<Player>(player);
}

void register_scenes(SceneHandler& scene_handler)
{
	scene_handler.add<StartMenu>(static_cast<int>(SceneName::StartMenu));
	scene_handler.add<BattleStage>(static_cast<int>(SceneName::BattleStage));
	scene_handler.add<GameOver>(static_cast<int>(SceneName::GameOver));
}

