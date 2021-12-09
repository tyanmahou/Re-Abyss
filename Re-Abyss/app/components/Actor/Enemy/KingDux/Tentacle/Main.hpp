#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/components/Actor/Enemy/KingDux/Tentacle/BuildDesc.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	class Main final :
		public IComponent
	{
	public:
		Main(ActorObj* pActor, const BuildDesc& desc);

		double getWaitTimeSec() const;
	private:
		ActorObj* m_pActor = nullptr;
		BuildDesc m_desc;
	};
}