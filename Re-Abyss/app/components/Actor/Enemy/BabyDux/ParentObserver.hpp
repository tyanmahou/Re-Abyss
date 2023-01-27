#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
	class ParentObserver final :
		public IComponent,
		public ILastUpdate
	{
	public:
		ParentObserver(ActorObj* pActor, ActorObj* pParent);

		void onStart() override;

		void onLastUpdate() override;
	private:
		ActorObj* m_pActor;

		Ref<DeadChecker> m_deadChecker;
		Ref<DeadChecker> m_parentDeadChecker;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::Enemy::BabyDux::ParentObserver>
	{
		using Base = MultiComponents<
			Actor::ILastUpdate
		>;
	};
}
