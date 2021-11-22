#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/ColSys/base/IExtension.hpp>

namespace abyss::Actor::Col
{
	class Receiver final : public ColSys::IExtension
	{
	public:
		struct Data{};
	public:
		Receiver(ActorObj* pActor):
			m_pActor(pActor)
		{}
		ColSys::ExtData data() const override
		{
			return Data{};
		}
	private:
		ActorObj* m_pActor;
	};
}