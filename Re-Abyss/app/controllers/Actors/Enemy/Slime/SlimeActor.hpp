#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

#include <abyss/components/Actors/Commons/StateCtrl.hpp>

namespace abyss
{
	struct SlimeEntity;
}
namespace abyss::Actor::Enemy::Slime
{
	class Senser;

	class SlimeActor : 
		public EnemyActor
	{
	private:
		Ref<StateCtrl> m_state;
	public:
		SlimeActor(const SlimeEntity& entity);

		bool accept(const ActVisitor& visitor) override;

		bool isWalk()const;
    };
}