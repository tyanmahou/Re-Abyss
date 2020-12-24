#include "RestartCtrl.hpp"
#include <Siv3D.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/modules/Event/Events.hpp>
#include <abyss/components/Events/GameRestart/Builder.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>

#include <abyss/components/Actors/Player/State/DeadState.hpp>

namespace abyss::Actor::Player
{
    RestartCtrl::RestartCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void RestartCtrl::onDead()
    {
        if (auto state = m_pActor->find<StateCtrl>()) {
            state->changeState<DeadState>();
        }
        // ゲームリスタートイベントを開始
        m_pActor->getModule<Events>()->create<Event::GameRestart::Builder>();
    }
}
