#include "RestartCtrl.hpp"
#include <Siv3D.hpp>
#include <abyss/modules/Actors/base/ActorObj.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Events/GameRestart/Builder.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>

#include <abyss/components/Actors/Player/State/DeadState.hpp>
#include <abyss/components/Actors/utils/StatePriority.hpp>

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
