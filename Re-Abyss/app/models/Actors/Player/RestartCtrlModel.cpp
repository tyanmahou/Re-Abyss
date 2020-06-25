#include "RestartCtrlModel.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Event/Events.hpp>
#include <abyss/controllers/Event/GameRestart/GameRestart.hpp>

namespace abyss::Player
{
    RestartCtrlModel::RestartCtrlModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void RestartCtrlModel::setup()
    {}

    void RestartCtrlModel::onDead()
    {
        // ゲームリスタートイベントを開始
        m_pActor->getModule<Events>()->create<Event::GameRestart>();
    }
}
