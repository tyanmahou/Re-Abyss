#include <abyss/components/Actor/Common/ColorAnim/InvinsibleColor.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/commons/ColorDef.hpp>

namespace abyss::Actor::ColorAnim
{
	InvinsibleColor::InvinsibleColor(ActorObj* pActor):
		m_pActor(pActor)
	{}

	void InvinsibleColor::startAnim(double sec)
	{
		m_colorAnimTimer.reset(sec);
	}

	void InvinsibleColor::endAnim()
	{
		m_colorAnimTimer.toEnd();
	}

	void InvinsibleColor::onStart()
	{
		m_damageCtrl = m_pActor->find<DamageCtrl>();
	}

	void InvinsibleColor::onPreDraw()
	{
		const double dt = m_pActor->deltaTime();
		m_colorAnimTimer.update(dt);
	}

	s3d::ColorF InvinsibleColor::colorAdd() const
	{
		return ColorDef::Invincible(m_damageCtrl->isInvincibleState(), m_colorAnimTimer.current(), m_colorAnimTimer.rate());
	}
}
