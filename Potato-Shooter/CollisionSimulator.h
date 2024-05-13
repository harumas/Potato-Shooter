#pragma once
#include <functional> 
#include <unordered_map>
#include "Extension.h"

using ValueGetter = std::function<int(void)>;
using ValueSetter = std::function<void(int)>;

struct Collision
{
	Collision(Vector2* pos, float radius) :
		position(pos),
		radius(radius)
	{}

	const	Vector2* position;
	const float radius;
};

struct SenderCollision
{
	SenderCollision(int channel, Vector2* pos, float radius, ValueGetter getter) :
		simulated(false),
		channel(channel),
		collision(Collision(pos, radius)),
		valueGetter(getter)
	{}

	bool simulated;
	int channel;
	const	Collision collision;
	const	ValueGetter valueGetter;
};

struct RecieverCollision
{
	RecieverCollision(int channel, Vector2* pos, float radius, ValueSetter setter) :
		simulated(false),
		channel(channel),
		collision(Collision(pos, radius)),
		valueSetter(setter)
	{}

	bool simulated;
	int channel;
	const	Collision collision;
	const ValueSetter valueSetter;
};

class CollisionSimulator
{
	std::vector<SenderCollision*> senders;
	std::vector<RecieverCollision*> recievers;

	bool collide(const Collision& p, const Collision& q);

public:
	void add_sender(SenderCollision* collision);
	void add_reciever(RecieverCollision* collision);
	void update();
	void reset();
	void debug_draw();
};

