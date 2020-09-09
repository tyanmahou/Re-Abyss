#include "RestartCtrl.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Event/Events.hpp>
#include <abyss/controllers/Event/GameRestart/GameRestart.hpp>
#include <abyss/components/Actors/Commons/StateCtrl.hpp>

#include <abyss/components/Actors/Player/State/DeadState.hpp>

namespace abyss::Actor::Player
{
    RestartCtrl::RestartCtrl(IActor* pActor):
        m_pActor(pActor)
    {}

    void RestartCtrl::setup()
    {}

    void RestartCtrl::onDead()
    {
        if (auto state = m_pActor->find<StateCtrl>()) {
            state->changeState<DeadState>();
        }
        // ゲームリスタートイベントを開始
        m_pActor->getModule<Events>()->create<Event::GameRestart>();
    }
}
