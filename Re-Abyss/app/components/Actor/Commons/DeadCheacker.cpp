#include "DeadCheacker.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>

#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Commons/IDeadCallback.hpp>

#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Actor;

    bool IsDead(const Ref<HP>& hp)
    {
        if (hp && hp->isDead()) {
            return true;
        }
        return false;
    }
}
namespace abyss::Actor
{
    DeadChecker::DeadChecker(ActorObj* pActor) :
        m_pActor(pActor)
    {}

    void DeadChecker::requestDead()
    {
        if (m_hp) {
            m_hp->setHp(0);
        }
        m_requestDead = true;
    }

    void DeadChecker::onStart()
    {
        m_hp = m_pActor->find<HP>();
    }

    void DeadChecker::onLastUpdate()
    {
        if (m_isDead) {
            return;
        }
        if (!m_requestDead && !IsDead(m_hp)) {
            return;
        }
        m_isDead = true;
        for (auto&& callback : m_pActor->finds<IDeadCallback>()) {
            callback->onDead();
        }
        if (m_isAutoDestroy) {
            m_pActor->destroy();
        }
    }
}
