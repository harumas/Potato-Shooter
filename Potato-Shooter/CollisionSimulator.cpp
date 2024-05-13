#include "CollisionSimulator.h"
#include "DxLib.h" 

void CollisionSimulator::add_sender(SenderCollision* collision)
{
	senders.emplace_back(collision);
}

void CollisionSimulator::add_reciever(RecieverCollision* collision)
{
	recievers.emplace_back(collision);
}

void CollisionSimulator::update()
{
	//判定を検出する側のループ 
	for (const SenderCollision* sender : senders)
	{
		if (!sender->simulated) continue;
		const	Collision& p = sender->collision;

		//判定を検出される側のループ 
		for (const RecieverCollision* reciever : recievers)
		{
			if (!reciever->simulated) continue;
			const Collision& q = reciever->collision;

			//当たったら
			if (sender->channel == reciever->channel && collide(p, q))
			{
				reciever->valueSetter(sender->valueGetter());
			}
		}
	}
}

bool CollisionSimulator::collide(const Collision& p, const Collision& q)
{
	const Vector2 dist = *q.position - *p.position;
	const float r = p.radius + q.radius;

	return dist.x * dist.x + dist.y * dist.y <= r * r;
}


void CollisionSimulator::reset()
{
	senders.clear();
	recievers.clear();
	senders.shrink_to_fit();
	recievers.shrink_to_fit();
}

//デバッグ描画
void CollisionSimulator::debug_draw()
{
	for (const SenderCollision* sender : senders)
	{
		if (!sender->simulated) continue;

		const unsigned int color = GetColor(255, 0, 0); //当てる側は赤
		const Vector2Int& pos = (Vector2Int)*sender->collision.position;
		DrawCircle(pos.x, pos.y, (int)sender->collision.radius, color);
	}

	for (const RecieverCollision* reciever : recievers)
	{
		if (!reciever->simulated) continue;

		const unsigned int color = GetColor(0, 0, 255); //当てられる側は青
		const Vector2Int& pos = (Vector2Int)*reciever->collision.position;
		DrawCircle(pos.x, pos.y, (int)reciever->collision.radius, color);
	}
}
