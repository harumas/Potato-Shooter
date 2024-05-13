#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <type_traits>

class ServiceLocator
{
public:
	ServiceLocator()
		:instances(),
		factories() {}

	~ServiceLocator()
	{
		clear();
	}

	//コンストラクタの引数が無いクラスを登録 
	template<typename T>
	void register_type()
	{
		T* instance = new T();
		register_instance(instance);
	}

	//インスタンスを登録
	template<typename T>
	void register_instance(T* instance)
	{
		const size_t hash = typeid(T).hash_code();

		if (instances.find(hash) == instances.end())
		{
			instances.emplace(hash, std::shared_ptr<void>(instance));
		}
	}

	//インスタンスの生成デリゲートを登録
	template<typename T>
	void register_factory(std::function<std::shared_ptr<T>()> factory) {
		const size_t hash = typeid(T).hash_code();

		if (factories.find(hash) == factories.end())
		{
			factories.emplace(hash, factory);
		}
	}

	//登録されたインスタンスを取得 
	template<typename T>
	std::shared_ptr<T> resolve() const
	{
		const size_t hash = typeid(T).hash_code();

		auto iterator_inst = instances.find(hash);
		if (iterator_inst != instances.end())
		{
			return std::static_pointer_cast<T>(iterator_inst->second);
		}

		auto iterator_fact = factories.find(hash);
		if (iterator_fact != factories.end())
		{
			return std::static_pointer_cast<T>(iterator_fact->second());
		}

		return NULL;
	}

	void clear()
	{
		instances.clear();
		factories.clear();
	}

private:
	std::unordered_map<size_t, std::shared_ptr<void>> instances;
	std::unordered_map<size_t, std::function<std::shared_ptr<void>()>> factories;
};
