#include "PlayerStateCtrl.hpp"
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>

namespace abyss::Event
{
    PlayerStateCtrl::PlayerStateCtrl(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void PlayerStateCtrl::onStart()
    {
        if (auto&& player = m_pEvent->getModule<Actor::Player::PlayerManager>()->getActor(); player && m_changer) {
            m_changer->onEventStart(player.get());
        }
    }
    void PlayerStateCtrl::onEnd()
    {
        if (auto&& player = m_pEvent->getModule<Actor::Player::PlayerManager>()->getActor(); player && m_changer) {
            m_changer->onEventEnd(player.get());
        }
    }
    PlayerStateCtrl& PlayerStateCtrl::setChanger(const std::shared_ptr<IPlayerStateChanger>& changer)
    {
        m_changer = changer;
        return *this;
    }
}
