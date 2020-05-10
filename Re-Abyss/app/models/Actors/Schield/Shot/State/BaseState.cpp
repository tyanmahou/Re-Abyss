#include "BaseState.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/Schield/Shot/ShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

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

    void BaseState::lastUpdate([[maybe_unused]]double dt)
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
