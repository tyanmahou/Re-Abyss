#include <abyss/components/Actor/Common/ColorAnim/BossInvinsibleColor.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/commons/ColorDef.hpp>

namespace abyss::Actor::ColorAnim
{
	BossInvinsibleColor::BossInvinsibleColor(ActorObj* pActor):
		m_pActor(pActor)
	{}

	void BossInvinsibleColor::startAnim(double sec)
	{
		m_colorAnimTimer.reset(sec);
	}

	void BossInvinsibleColor::endAnim()
	{
		m_colorAnimTimer.toEnd();
	}

	void BossInvinsibleColor::onStart()
	{
		m_damageCtrl = m_pActor->find<DamageCtrl>();
	}

	void BossInvinsibleColor::onPreDraw()
	{
		const double dt = m_pActor->deltaTime();
		m_colorAnimTimer.update(dt);
	}

	s3d::ColorF BossInvinsibleColor::colorAdd() const
	{
		return ColorDef::Invincible(m_damageCtrl->isInvincibleState(), m_colorAnimTimer.current(), m_colorAnimTimer.rate());
	}
}
