#include "WeaponCollection.h"

WeaponCollection::WeaponCollection(Vector2* position, ResourceHandler* handler_ptr, CollisionSimulator* simulator_ptr) :
	base_point(position),
	handler_ptr(handler_ptr),
	simulator_ptr(simulator_ptr)
{}

void WeaponCollection::shoot(Vector2 initial_velocity)
{
	for (Weapon* weapon : weapons)
	{
		weapon->shoot(initial_velocity);
	}
}

void WeaponCollection::set_channels(int channel)
{
	for (Weapon* weapon : weapons)
	{
		weapon->set_channel(channel);
	}

	weapon_collide_channel = channel;
}

void WeaponCollection::update(const double& dt)
{
	for (Weapon* weapon : weapons)
	{
		weapon->update(dt);
	}
}

void WeaponCollection::draw()
{
	for (Weapon* weapon : weapons)
	{
		weapon->draw();
	}
}


WeaponCollection::~WeaponCollection()
{
	for (Weapon* weapon : weapons)
	{
		delete weapon;
	}
}

void WeaponCollection::reset_all()
{
	for (Weapon* weapon : weapons)
	{
		weapon->reset();
	}
}
