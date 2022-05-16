#include <abyss/components/Actor/Common/ColorAnim/BossDeadColor.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <Siv3D.hpp>

namespace abyss::Actor::ColorAnim
{
	BossDeadColor::BossDeadColor(ActorObj* pActor):
		m_pActor(pActor)
	{
	}
	void BossDeadColor::startAnim(double blackFadeSec, double alphaFadeSec)
	{
		m_isStarted = true;
		m_blackFadeTimer.reset(blackFadeSec);
		m_alphaFadeTimer.reset(alphaFadeSec);
	}
	void BossDeadColor::onPreDraw()
	{
		double dt = m_pActor->deltaTime();
		dt = m_blackFadeTimer.update(dt);
		dt = m_alphaFadeTimer.update(dt);
	}
	s3d::ColorF BossDeadColor::colorMul() const
	{
		if (!m_isStarted) {
			return s3d::ColorF(1, 1);
		}
		return s3d::ColorF(
			m_blackFadeTimer.invRate(),
			m_alphaFadeTimer.invRate()
		);
	}
}
