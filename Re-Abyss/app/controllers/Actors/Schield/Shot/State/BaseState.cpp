#include "BaseState.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/Schield/Shot/ShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss::Schield::Shot
{
    void BaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }

    void BaseState::update(double dt)
    {
        m_body->update(dt);
        // 画面外判定
        if (!m_actor->getModule<Camera>()->inRoom(m_actor->getColliderCircle())) {
            m_actor->destroy();
        }
    }

    void BaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const Receiver&) {
            // 当たって消える
            m_actor->destroy();
        });
    }

    void BaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }

}
