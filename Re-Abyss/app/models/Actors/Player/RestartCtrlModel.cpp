#include "RestartCtrlModel.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Master/Master.hpp>

namespace abyss::Player
{
    RestartCtrlModel::RestartCtrlModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void RestartCtrlModel::setup()
    {}

    void RestartCtrlModel::onDead()
    {
        m_pActor->getModule<Master>()->restart();
    }
}
