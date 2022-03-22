#include <abyss/components/Actor/Enemy/CodeZero/HideCtrl.hpp>

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
	HideCtrl::HideCtrl(ActorObj* pActor):
		m_pActor(pActor)
	{}

	void HideCtrl::setup([[maybe_unused]]Executer executer)
	{
	}
	void HideCtrl::onStart()
	{
	}
	void HideCtrl::onEnd()
	{
	}
	void HideCtrl::onDraw() const
	{
		m_pActor->getModule<RoomManager>()->currentRoom().getRegion().draw(ColorF(0, 1));
	}
}
