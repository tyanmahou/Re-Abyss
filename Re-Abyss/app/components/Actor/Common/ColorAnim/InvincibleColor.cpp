#include <abyss/components/Actor/Common/ColorAnim/InvincibleColor.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/commons/ColorDef.hpp>

namespace abyss::Actor::ColorAnim
{
	InvincibleColor::InvincibleColor(ActorObj* pActor):
		m_pActor(pActor)
	{}

	void InvincibleColor::startAnim(double sec)
	{
		m_colorAnimTimer.reset(sec);
	}

	void InvincibleColor::endAnim()
	{
		m_colorAnimTimer.toEnd();
	}

	void InvincibleColor::onStart()
	{
		m_damageCtrl = m_pActor->find<DamageCtrl>();
	}

	void InvincibleColor::onPreDraw()
	{
		const double dt = m_pActor->deltaTime();
		m_colorAnimTimer.update(dt);
	}

	s3d::ColorF InvincibleColor::colorAdd() const
	{
		return ColorDef::Invincible(m_damageCtrl->isInvincibleState(), m_colorAnimTimer.current(), m_colorAnimTimer.rate());
	}
}
