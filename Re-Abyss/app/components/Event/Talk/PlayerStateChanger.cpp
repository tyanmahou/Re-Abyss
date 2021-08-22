#include "PlayerStateChanger.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Player/State/TalkState.hpp>
#include <abyss/components/Actor/Player/State/SwimState.hpp>

namespace abyss::Event::Talk
{
    void PlayerStateChanger::onEventStart(Actor::ActorObj* player)
    {
        player->find<Actor::StateCtrl>()->changeState<Actor::Player::TalkState>(
            m_pTargetLocator
            );
    }
    void PlayerStateChanger::onEventEnd(Actor::ActorObj * player)
    {
        player->find<Actor::StateCtrl>()->changeState<Actor::Player::SwimState>();
    }
}
