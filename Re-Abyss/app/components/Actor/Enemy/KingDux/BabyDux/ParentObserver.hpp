#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/GameObject/WeakObject.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
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
		WeakObject m_parent;

		Ref<DeadChecker> m_deadChecker;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::Enemy::KingDux::BabyDux::ParentObserver>
	{
		using Base = MultiComponents<
			Actor::ILastUpdate
		>;
	};
}
