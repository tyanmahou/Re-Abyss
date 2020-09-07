#include "DebugCtrlModel.hpp"
#if ABYSS_DEBUG
#include <Siv3D.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
namespace abyss::Actor::Player
{
    DebugCtrlModel::DebugCtrlModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void DebugCtrlModel::setup()
    {}

    void DebugCtrlModel::onUpdate([[maybe_unused]]double dt)
    {
        auto hp = m_pActor->find<HPModel>();
        if (KeyD.down()) {
            hp->setHp(0);
        }
        if (KeyS.down()) {
            hp->reset();
        }
    }

}
#endif