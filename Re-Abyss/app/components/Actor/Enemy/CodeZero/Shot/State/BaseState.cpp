#include "BaseState.hpp"
#include <abyss/components/Actor/Commons/HP.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    void BaseState::onCache()
    {
        m_parent = m_pActor->find<ParentCtrl>().get();
        m_body = m_pActor->find<Body>().get();
        m_scale = m_pActor->find<ScaleCtrl>().get();
        m_view = m_pActor->find<ViewCtrl<ShotVM>>().get();
    }
    void BaseState::lastUpdate()
    {
        if (m_parent->getHp()->isDead()) {
            m_pActor->destroy();
        }
    }

    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
