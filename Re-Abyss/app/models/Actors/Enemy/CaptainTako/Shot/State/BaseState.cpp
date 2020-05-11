#include "BaseState.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/Enemy/CaptainTako/Shot/ShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss::CaptainTako::Shot
{
    void BaseState::setup()
    {
        m_body = m_pActor->find<BodyModel>().get();
    }

    void BaseState::start()
    {

    }

    void BaseState::update(double dt)
    {
        m_body->update(dt);
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
