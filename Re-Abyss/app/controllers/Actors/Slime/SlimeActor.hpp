#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
	class SlimeActor : 
		public EnemyActor
	{
	public:
		enum class Motion
		{
			Walk,
			Jump
		};
	private:
		class Cencer;
		std::shared_ptr<Cencer> m_cencer;
		std::shared_ptr<SlimeVM> m_view;
		Motion m_motion = Motion::Walk;

		bool m_onCollision = false;
		void onCollision(const MapActor& map);
	public:
		SlimeActor(const s3d::Vec2& pos, Forward forward = Forward::Left);

		void start()override;
		void update(double)override;
		void draw()const;

		void onCollisionEnter(ICollider* col) override;
		void onCollisionStay(ICollider* col) override;

		CShape getCollider() const override;
		s3d::RectF region()const;
		Motion getMotion()const;

		void reverse();

		void accept(const ActVisitor& visitor) override;
	};
}