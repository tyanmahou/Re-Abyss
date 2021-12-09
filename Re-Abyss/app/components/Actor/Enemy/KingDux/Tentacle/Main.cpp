#include "Main.hpp"

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
	Main::Main(ActorObj* pActor, const BuildDesc& desc):
		m_pActor(pActor),
		m_desc(desc)
	{
	}
	double Main::getWaitTimeSec() const
	{
		return m_desc.waitTimeSec;
	}
}