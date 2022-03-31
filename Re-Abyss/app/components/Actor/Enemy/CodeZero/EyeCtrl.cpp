#include <abyss/components/Actor/Enemy/CodeZero/EyeCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	EyeCtrl::EyeCtrl(ActorObj* pActor):
		m_pActor(pActor)
	{}
	void EyeCtrl::setVisible(bool isVisible, double fadeSec)
	{
		m_isVisible = isVisible;
		m_timer.reset(fadeSec);
	}
	bool EyeCtrl::isAnimEnd() const
	{
		return m_timer.isEnd();
	}
	void EyeCtrl::flush(double timeSec)
	{
		m_flushTimer.reset(timeSec);
	}
	double EyeCtrl::scale() const
	{
		return s3d::Math::Lerp(1.0, 1.2, m_flushTimer.invRate());
	}
	void EyeCtrl::onPreDraw()
	{
		auto dt = m_pActor->deltaTime();
		m_timer.update(dt);
		m_flushTimer.update(dt);
	}
	s3d::ColorF EyeCtrl::colorMul() const
	{
		auto alpha = m_isVisible ? m_timer.rate() : m_timer.invRate();
		return ColorF(1, alpha);
	}
	s3d::ColorF EyeCtrl::colorAdd() const
	{
		return ColorF(m_flushTimer.invRate(), 0.0);
	}
}