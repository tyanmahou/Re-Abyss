#include <abyss/components/Actor/Enemy/CodeZero/HideCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	HideCtrl::HideCtrl(ActorObj* pActor):
		m_pActor(pActor)
	{}

	void HideCtrl::setVisible(bool isVisible, double fadeSec)
	{
		m_isVisible = isVisible;
		m_timer.reset(fadeSec);
	}

	bool HideCtrl::isAnimEnd() const
	{
		return m_timer.isEnd();
	}
	double HideCtrl::calcBackAlpha() const
	{
		auto alpha = m_isVisible ? m_timer.invRate() : m_timer.rate();
		return alpha;
	}
	void HideCtrl::setup([[maybe_unused]]Executer executer)
	{
	}
	void HideCtrl::onStart()
	{
	}
	void HideCtrl::onEnd()
	{
	}
	void HideCtrl::onPreDraw()
	{
		auto dt = m_pActor->deltaTime();
		m_timer.update(dt);
	}
	void HideCtrl::onDraw() const
	{
		auto alpha = this->calcBackAlpha();
		m_pActor->getModule<RoomManager>()->currentRoom().getRegion().draw(ColorF(0, alpha));
	}
	s3d::ColorF HideCtrl::colorMul() const
	{
		auto alpha = m_isVisible ? m_timer.rate() : m_timer.invRate();
		return ColorF(1, alpha);
	}
}
