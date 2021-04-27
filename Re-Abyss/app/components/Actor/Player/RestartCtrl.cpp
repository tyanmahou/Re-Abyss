#include "RestartCtrl.hpp"
#include <Siv3D.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Events/GameRestart/Builder.hpp>
#include <abyss/components/Actor/Commons/StateCtrl.hpp>

#include <abyss/components/Actor/Player/State/DeadState.hpp>
#include <abyss/components/Actor/utils/StatePriority.hpp>

namespace abyss::Actor::Player
{
    RestartCtrl::RestartCtrl(ActorObj* pActor):
        m_pActor(pActor)
    {}

    void RestartCtrl::onDead()
    {
        if (auto state = m_pActor->find<StateCtrl>()) {
            state->changeState<DeadState, StatePriority::Dead>();
        }
        // ゲームリスタートイベントを開始
        m_pActor->getModule<Events>()->create<Event::GameRestart::Builder>();
    }
}
