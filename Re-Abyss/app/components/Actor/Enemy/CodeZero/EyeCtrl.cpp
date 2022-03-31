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
	void EyeCtrl::onPreDraw()
	{
		auto dt = m_pActor->deltaTime();
		m_timer.update(dt);
	}
	s3d::ColorF EyeCtrl::colorMul() const
	{
		auto alpha = m_isVisible ? m_timer.rate() : m_timer.invRate();
		return ColorF(1, alpha);
	}
}