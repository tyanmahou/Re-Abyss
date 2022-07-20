#include <abyss/components/Novel/Common/TalkCtrl.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/components/Actor/Player/State/TalkState.hpp>
#include <abyss/components/Actor/Player/State/SwimState.hpp>

namespace abyss::Novel
{
    TalkCtrl::TalkCtrl(TalkObj* pTalk):
        m_pTalk(pTalk)
    {
    }
    void TalkCtrl::request()
    {
        if (auto&& player = m_pTalk->getModule<Actor::Player::PlayerManager>()->getActor()) {
            Actor::Player::TalkState::Change(player.get(), m_pTargetLocator);
        }
    }
    void TalkCtrl::resume()
    {
        if (auto&& player = m_pTalk->getModule<Actor::Player::PlayerManager>()->getActor()) {
            player->find<Actor::StateCtrl>()->changeState<Actor::Player::SwimState>();
        }
    }
}
