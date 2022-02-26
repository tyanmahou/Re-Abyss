#include <abyss/components/Actor/Enemy/KingDux/BabyCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
	BabyCtrl::BabyCtrl(ActorObj* pActor):
		m_pActor(pActor)
	{
	}
	void BabyCtrl::add(const Ref<ActorObj>& baby)
	{
		m_babies << baby;
	}
	void BabyCtrl::onLastUpdate()
	{
		s3d::Erase_if(m_babies, [](const Ref<ActorObj>& obj) {
			return !obj || obj->isDestroyed();
		});
	}
	bool BabyCtrl::isExistBaby() const
	{
		return !m_babies.isEmpty();
	}
}
