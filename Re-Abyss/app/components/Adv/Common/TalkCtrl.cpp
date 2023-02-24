#include <abyss/components/Adv/Common/TalkCtrl.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/components/Actor/Player/State/TalkState.hpp>
#include <abyss/components/Actor/Player/State/SwimState.hpp>

namespace abyss::Adv
{
    TalkCtrl::TalkCtrl(AdvObj* pObj):
        m_pObj(pObj)
    {
    }
    void TalkCtrl::request()
    {
        if (auto&& player = m_pObj->getModule<Actor::Player::PlayerManager>()->getActor()) {
            Actor::Player::TalkState::Change(player.get(), m_pTargetLocator);
        }
    }
    void TalkCtrl::resume()
    {
        if (auto&& player = m_pObj->getModule<Actor::Player::PlayerManager>()->getActor()) {
            player->find<Actor::StateCtrl>()->changeState<Actor::Player::SwimState>();
        }
    }
}
