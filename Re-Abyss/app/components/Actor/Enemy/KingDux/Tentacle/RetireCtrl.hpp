#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/base/IMove.hpp>
#include <abyss/components/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	class RetireCtrl :
		public IComponent,
		public IMove,
		public IPostCollision,
		public IStateCallback
	{
	public:
		RetireCtrl(ActorObj* pActor);

		void onStart() override;
		void onMove()override;
		void onPostCollision()override;
		void onStateStart() override;
		void setActive(bool isActive)
		{
			m_isActive = isActive;
		}
	private:
		ActorObj* m_pActor;
		Ref<Body> m_body;
		Ref<RotateCtrl> m_rotCtrl;
		Ref<ColCtrl> m_colCtrl;
		bool m_isActive = true;

		double m_accel = 1440;
		double m_speed = 0;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::Enemy::KingDux::Tentacle::RetireCtrl>
	{
		using Base = MultiComponents<
			Actor::IMove,
			Actor::IPostCollision,
			Actor::IStateCallback
		>;
	};
}