#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/base/ILastUpdate.hpp>
#include <abyss/modules/GameObject/WeakObject.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
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
		WeakObject m_parent;
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
