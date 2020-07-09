#include "RestartCtrlModel.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>

namespace abyss::Player
{
    RestartCtrlModel::RestartCtrlModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void RestartCtrlModel::setup()
    {}

    void RestartCtrlModel::onDead()
    {
        if (auto state = m_pActor->find<StateModel<PlayerActor>>()) {
            state->changeState(PlayerActor::State::Dead);
        }
    }
}
