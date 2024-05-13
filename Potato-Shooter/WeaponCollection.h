#pragma once
#include "Weapon.h" 

class WeaponCollection
{
private:
	ResourceHandler* handler_ptr;
	CollisionSimulator* simulator_ptr;
	const Vector2* base_point;

	vector<Weapon*> weapons;
	int weapon_collide_channel;

public:
	WeaponCollection(Vector2* base_point, ResourceHandler* handler_ptr, CollisionSimulator* simulator_ptr);
	~WeaponCollection();

	void set_channels(int channel);
	void shoot(Vector2 initial_velocity);
	void update(const double& dt);
	void draw();
	void reset_all();

	template<typename T>
	T* add_weapon()
	{
		T* weapon = new T();
		Weapon* base = weapon;

		weapons.emplace_back(base);
		base->set_channel(weapon_collide_channel);
		base->load(handler_ptr, simulator_ptr);
		base->create(base_point);

		return weapon;
	};
};
