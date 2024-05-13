#include "WeaponA.h"

BulletA::BulletA(int channel) :
	collider(channel, &position, 6, [&]()
		{
			disable();
return this->damage_point;
		})
{}

		void BulletA::enable()
		{
			is_alive = true;
			collider.simulated = true;
		}

		void BulletA::disable()
		{
			is_alive = false;
			collider.simulated = false;

			position = Vector2(0, 0);
		}

		bool BulletA::exist() const
		{
			return is_alive;
		}

		WeaponA::WeaponA() : bullet_handle(5), bullet_count(10) {}

		WeaponA::~WeaponA()
		{
			for (BulletA* bullet : bullets)
			{
				delete bullet;
			}
		}

		void WeaponA::load(ResourceHandler* handler_ptr, CollisionSimulator* simulator)
		{
			Weapon::load(handler_ptr, simulator);

			bullet_handle = handler->load_graph("bullet_A.png");
		}

		void WeaponA::create(const Vector2* base_point)
		{
			this->base_point = base_point;
			bullet_count = 10;
			bullets.clear();
			bullets.shrink_to_fit();
			bullets.reserve(bullet_count);


			for (int i = 0; i < bullet_count; i++)
			{
				BulletA* bullet = new BulletA(collide_channel);
				bullets.push_back(bullet);
				simulator->add_sender(&bullet->collider); //コライダーを登録
			}
		}

		void WeaponA::shoot(Vector2 initial_velocity)
		{
			for (BulletA* bullet : bullets)
			{
				if (bullet->exist()) continue;

				bullet->position = *base_point;
				bullet->velocity = initial_velocity;
				bullet->enable();

				break;
			}
		}

		void WeaponA::update(const double& dt)
		{
			for (BulletA* bullet : bullets)
			{
				if (!bullet->exist()) continue;

				update_bullet(bullet, dt);
			}
		}

		void WeaponA::update_bullet(BulletA* bullet, const double& dt)
		{
			bullet->position += bullet->velocity * (float)dt;

			update_bullet_status(bullet);
		}


		void WeaponA::update_bullet_status(BulletA* bullet)
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

		void WeaponA::draw()
		{
			for (const BulletA* bullet : bullets)
			{
				if (!bullet->exist()) continue;

				const Vector2Int& pos = (Vector2Int)bullet->position;
				handler->draw_extend_graph(pos.x, pos.y, 1.5, bullet_handle);
			}
		}

		void WeaponA::reset()
		{
			for (BulletA* bullet : bullets)
			{
				if (!bullet->exist()) continue;

				bullet->disable();
			}
		}

