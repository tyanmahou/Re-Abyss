#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

#include <abyss/controllers/Actors/base/IState.hpp>

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
		enum State
		{
			Walk,
			Jump
		};
	private:
		class Cencer;
		std::shared_ptr<Cencer> m_cencer;
		StateManager<SlimeActor> m_state;
		std::shared_ptr<SlimeVM> m_view;
		Motion m_motion = Motion::Walk;

		bool m_onCollision = false;
	public:
		SlimeActor(const s3d::Vec2& pos, Forward forward = Forward::Left);

		void start()override;
		void update(double)override;
		void draw()const;

		void onCollisionStay(ICollider* col) override;

		CShape getCollider() const override;
		s3d::RectF region()const;
		Motion getMotion()const;

		void reverse();

		void accept(const ActVisitor& visitor) override;

		SlimeVM* getBindedView()const;
	};
}