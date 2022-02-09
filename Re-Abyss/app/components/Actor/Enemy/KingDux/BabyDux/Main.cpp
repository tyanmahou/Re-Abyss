#include <abyss/components/Actor/Enemy/KingDux/BabyDux/Main.hpp>

namespace abyss::Actor::Enemy::KingDux::BabyDux
{
	Main::Main(ActorObj* pActor, const BuildDesc& desc, const s3d::Vec2& parentPos):
		m_pActor(pActor),
		m_desc(desc),
		m_parentPos(parentPos)
	{
	}
}