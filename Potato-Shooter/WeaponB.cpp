#include "WeaponB.h"

BulletB::BulletB(int channel) :
	collider(channel, &position, 4, [&]()
		{
			disable();
return this->damage_point;
		})
{}

		void BulletB::enable()
		{
			is_alive = true;
			collider.simulated = true;
		}

		void BulletB::disable()
		{
			is_alive = false;
			collider.simulated = false;

			position = Vector2(0, 0);
		}

		bool BulletB::exist() const
		{
			return is_alive;
		}

		WeaponB::~WeaponB()
		{
			for (BulletB* bullet : bullets)
			{
				delete bullet;
			}
		}

		void WeaponB::load(ResourceHandler* handler_ptr, CollisionSimulator* simulator)
		{
			Weapon::load(handler_ptr, simulator);
		}

		void WeaponB::create(const Vector2* base_point)
		{
			this->base_point = base_point;

			bullets.clear();
			bullets.shrink_to_fit();
			bullets.reserve(bullet_count);

			for (int i = 0; i < bullet_count; i++)
			{
				BulletB* bullet = new BulletB(collide_channel);
				bullets.push_back(bullet);
				simulator->add_sender(&bullet->collider); //コライダーを登録
			}
		}

		void WeaponB::set_target(const Vector2* target)
		{
			this->target = target;
		}

		Vector2 WeaponB::calc_direction()
		{
			return  (*target - *base_point).normalized();
		}

		Vector2 WeaponB::calc_right()
		{
			return  (Vector2(target->y, base_point->x) - Vector2(base_point->y, target->x)).normalized();
		}

		void WeaponB::shoot(Vector2 initial_velocity)
		{
			int flip = is_flip_shoot ? -1 : 1;
			Vector2 dir = calc_direction();
			Vector2 range = calc_right() * shoot_range * (float)flip;

			for (BulletB* bullet : bullets)
			{
				if (bullet->exist()) continue;

				bullet->position = *base_point + range;
				bullet->velocity = dir * initial_velocity.y;
				bullet->shoot_dir = dir;
				bullet->enable();

				break;
			}

			is_flip_shoot = !is_flip_shoot;
		}

		void WeaponB::update(const double& dt)
		{
			for (BulletB* bullet : bullets)
			{
				if (!bullet->exist()) continue;

				update_bullet(bullet, dt);
			}
		}

		void WeaponB::update_bullet(BulletB* bullet, const double& dt)
		{
			bullet->position += bullet->velocity * (float)dt;

			update_bullet_status(bullet);
		}


		void WeaponB::update_bullet_status(BulletB* bullet)
		{
			const Vector2& pos = bullet->position;
			const float& radius = bullet->collider.collision.radius;

			bool out_of_w = pos.x < -radius || pos.x > App::screen_w + radius;
			bool out_of_h = pos.y < -radius || pos.y > App::screen_h + radius;

			//画面上部の外に出たら無効化
			if (out_of_w || out_of_h)
			{
				bullet->disable();
			}
		}

		void WeaponB::draw()
		{
			for (const BulletB* bullet : bullets)
			{
				if (!bullet->exist()) continue;

				const float& radius = bullet->collider.collision.radius;
				const Vector2& pos = bullet->position;
				const Vector2 dir = bullet->shoot_dir;
				const Vector2 p1 = pos + dir * radius;
				const Vector2 p2 = p1 - dir * bullet_height;

				DrawLineAA(p1.x, p1.y, p2.x, p2.y, GetColor(250, 231, 87), radius * 2);
			}
		}

		void WeaponB::reset()
		{
			for (BulletB* bullet : bullets)
			{
				if (!bullet->exist()) continue;

				bullet->disable();
			}
		}

