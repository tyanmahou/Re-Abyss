#include <abyss/components/Novel/Common/PlayerCtrl.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>

namespace abyss::Novel
{
    PlayerCtrl::PlayerCtrl(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}
    void PlayerCtrl::request(std::function<void(Actor::ActorObj*)> callback)
    {
        if (auto&& player = m_pTalk->getModule<Actor::Player::PlayerManager>()->getActor()) {
            callback(player.get());
        }
    }
}
