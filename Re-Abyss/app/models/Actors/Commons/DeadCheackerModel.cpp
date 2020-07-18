#include "DeadCheackerModel.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Master/Master.hpp>

#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/models/Actors/base/IDeadCallbackModel.hpp>

#include <Siv3D.hpp>

namespace
{
    using namespace abyss;

    bool IsDead(const Ref<HPModel>& hp)
    {
        if (hp && hp->isDead()) {
            return true;
        }
        return false;
    }
}
namespace abyss
{
    DeadCheckerModel::DeadCheckerModel(IActor* pActor) :
        m_pActor(pActor)
    {}

    void DeadCheckerModel::requestDead()
    {
        if (m_hp) {
            m_hp->setHp(0);
        }
        m_requestDead = true;
    }

    void DeadCheckerModel::setup()
    {
        m_hp = m_pActor->find<HPModel>();
    }

    void DeadCheckerModel::onLastUpdate()
    {
        if (m_isDead) {
            return;
        }
        if (!m_requestDead && !IsDead(m_hp)) {
            return;
        }
        m_isDead = true;
        for (auto&& callback : m_pActor->finds<IDeadCallbackModel>()) {
            callback->onDead();
        }
        if (m_isAutoDestroy) {
            m_pActor->destroy();
        }
    }
}
