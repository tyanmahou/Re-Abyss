#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
	class SlimeSenser;

	class SlimeActor : 
		public EnemyActor
	{
	public:
		enum State
		{
			Walk,
			Jump
		};
	private:
		std::shared_ptr<SlimeSenser> m_senser;

		StateManager<SlimeActor> m_state;
		std::shared_ptr<SlimeVM> m_view;
	public:
		SlimeActor(const SlimeEntity& entity);

		void start()override;
		void update(double)override;
		void draw()const;

		void onCollisionStay(ICollider* col) override;

		bool accept(const ActVisitor& visitor) override;

		SlimeVM* getBindedView()const;

		bool isWalk()const;

		void onDead()override;
        void lastUpdate(double dt) override;
    };
}