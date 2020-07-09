#include "DebugCtrlModel.hpp"
#if ABYSS_DEBUG
#include <Siv3D.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
namespace abyss::Player
{
    DebugCtrlModel::DebugCtrlModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void DebugCtrlModel::setup()
    {}

    void DebugCtrlModel::onUpdate([[maybe_unused]]double dt)
    {
        if (KeyD.down()) {
            m_pActor->find<HPModel>()->setHp(0);
        }
    }

}
#endif