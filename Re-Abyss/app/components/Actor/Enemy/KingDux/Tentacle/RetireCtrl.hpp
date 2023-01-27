#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/modules/Actor/base/IPostUpdate.hpp>
#include <abyss/modules/Actor/base/IMove.hpp>
#include <abyss/modules/Actor/base/IPostCollision.hpp>
#include <abyss/components/Actor/Common/IStateCallback.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	class RetireCtrl :
		public IComponent,
		public IPostUpdate,
		public IMove,
		public IPostCollision,
		public IStateCallback
	{
	public:
		RetireCtrl(ActorObj* pActor);

		void setup(Executer executer)override;
		void onStart() override;
		void onPostUpdate()override;
		void onMove()override;
		void onPostCollision()override;
		void onStateStart() override;
		void setActive(bool isActive)
		{
			m_isActive = isActive;
		}
		void requestReturn()
		{
			m_isRetire = true;
		}
		bool isRetire() const
		{
			return m_isRetire;
		}

		void setIsReturnState(bool isReturnState)
		{
			m_isReturnState = isReturnState;
		}
	private:
		ActorObj* m_pActor;
		Ref<Body> m_body;
		Ref<RotateCtrl> m_rotCtrl;
		Ref<ColCtrl> m_colCtrl;
		bool m_isActive = true;

		double m_accel = 1440;
		double m_speed = 0;

		bool m_isRetire = false;
		bool m_isReturnState = false;
	};
}

namespace abyss
{
	template<>
	struct ComponentTree<Actor::Enemy::KingDux::Tentacle::RetireCtrl>
	{
		using Base = MultiComponents<
			Actor::IPostUpdate,
			Actor::IMove,
			Actor::IPostCollision,
			Actor::IStateCallback
		>;
	};
}