#pragma once
#include "ServiceLocator.h" 
#include "ResourceHandler.h" 
#include "Device.h"

//シーンクラス 
class Scene
{
public:
	bool initialized = false;

	virtual void load(ServiceLocator& locator) {
		handler = locator.resolve<ResourceHandler>();
		device = locator.resolve<Device>();
	};

	virtual void init() = 0;
	virtual int update() = 0;
	virtual void draw() = 0;
	virtual void clear() = 0;

protected:
	std::shared_ptr<ResourceHandler> handler;
	std::shared_ptr<Device> device;

	int quit()
	{
		return -1;
	}

	int proceed()
	{
		return 0;
	}
};


//シーン管理クラス 
class SceneHandler
{
public:

	//シーンをゲームに追加 
	template<typename T>
	void add(int key)
	{
		T* scene = new T();
		Scene* base = scene;

		if (scenes.count(key) == 0)
		{
			scenes.emplace(key, base);
		}
	}

	//シーンを全てロード
	void load_all(ServiceLocator& locator)
	{
		for (std::pair<const int, Scene*>& scene : scenes)
		{
			scene.second->load(locator);
		}
	}

	//シーンを切り替え
	Scene* switch_to(int key)
	{
		if (scenes.count(key) > 0)
		{
			if (current != nullptr)
			{
				current->initialized = false;
			}

			current = scenes[key];
		}

		return current;
	}

	//現在のシーンを取得 
	Scene* get_current() {
		return current;
	}

private:
	Scene* current = nullptr;
	std::unordered_map<int, Scene*> scenes;
};



