#include "DeadCheackerModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Master/Master.hpp>

#include <abyss/models/Actors/Commons/HPModel.hpp>

#include <Siv3D.hpp>

namespace
{
    using namespace abyss;

    bool IsDead(IActor* pActor, const Ref<HPModel>& hp)
    {
        if (!hp || hp->isDead()) {
            return true;
        }
        if (s3d::KeyD.down()) {
            return true;
        }
        return false;
    }
}
namespace abyss::Player
{
    DeadCheckerModel::DeadCheckerModel(IActor* pActor):
        m_pActor(pActor)
    {}

    void DeadCheckerModel::setup()
    {
        m_hp = m_pActor->find<HPModel>();
    }

    void DeadCheckerModel::onLastUpdate([[maybe_unused]]double dt)
    {
        if (!IsDead(m_pActor, m_hp)) {
            return;
        }

        m_pActor->getModule<Master>()->restart();
    }

}
