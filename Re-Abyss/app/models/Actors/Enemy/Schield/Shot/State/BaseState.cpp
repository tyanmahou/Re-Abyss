#include "BaseState.hpp"

#include <abyss/controllers/System/System.hpp>
#include <abyss/views/Actors/Enemy/Schield/Shot/ShotVM.hpp>
#include <abyss/controllers/Actors/ActInclude.hpp>

namespace abyss::Schield::Shot
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
    }

    void BaseState::update(double dt)
    {
        m_body->update(dt);
    }

    void BaseState::lastUpdate()
    {
        // 画面外判定
        if (!m_pActor->getModule<Camera>()->inRoom(m_pActor->getColliderCircle())) {
            m_pActor->destroy();
        }
    }
    void BaseState::draw() const
    {
        m_pActor->getBindedView()->draw();
    }

}
