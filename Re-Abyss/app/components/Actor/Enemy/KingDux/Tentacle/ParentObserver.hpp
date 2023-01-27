#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Actor/base/ILastUpdate.hpp>
#include <abyss/components/Actor/Common/DeadCheacker.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	class ParentObserver final :
		public IComponent,
		public ILastUpdate
	{
	public:
		ParentObserver(ActorObj* pActor, ActorObj* pParent);

		void onLastUpdate() override;
	private:
		ActorObj* m_pActor;
		Ref<DeadChecker> m_parentDeadChecker;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::Enemy::KingDux::Tentacle::ParentObserver>
	{
		using Base = MultiComponents<
			Actor::ILastUpdate
		>;
	};
}
