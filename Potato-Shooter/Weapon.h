#pragma once

#include "Extension.h"
#include "Module.h" 

class Weapon
{
protected:
	ResourceHandler* handler = nullptr;
	CollisionSimulator* simulator = nullptr;
	const	Vector2* base_point = nullptr;

	int collide_channel = 0;

public:
	virtual	void load(ResourceHandler* handler, CollisionSimulator* simulator)
	{
		this->handler = handler;
		this->simulator = simulator;
	};

	void set_channel(int channel)
	{
		collide_channel = channel;
	};

	virtual void shoot(Vector2 initial_velocity) = 0;
	virtual void create(const Vector2* base_point) = 0;
	virtual void update(const double& dt) = 0;
	virtual void draw() = 0;
	virtual void reset() = 0;
};

