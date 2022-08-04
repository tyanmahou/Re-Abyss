#include <abyss/components/Actor/Enemy/BabyDux/Main.hpp>

namespace abyss::Actor::Enemy::BabyDux
{
	Main::Main(ActorObj* pActor, const BuildDesc& desc, const s3d::Vec2& parentPos):
		m_pActor(pActor),
		m_desc(desc),
		m_parentPos(parentPos)
	{
	}
	double Main::getAppearTime() const
	{
		return m_desc.appearTime;
	}
	const s3d::Vec2& Main::getAppearMove() const
	{
		return m_desc.appearMove;
	}
}
