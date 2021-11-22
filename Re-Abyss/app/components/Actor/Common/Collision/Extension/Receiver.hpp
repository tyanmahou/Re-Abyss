#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/Collision/base/IExtension.hpp>

namespace abyss::Actor::Collision
{
	class Receiver final : public abyss::Collision::IExtension
	{
	public:
		struct Data{};
	public:
		Receiver(ActorObj* pActor):
			m_pActor(pActor)
		{}
		abyss::Collision::ExtData data() const override
		{
			return Data{};
		}
	private:
		ActorObj* m_pActor;
	};
}