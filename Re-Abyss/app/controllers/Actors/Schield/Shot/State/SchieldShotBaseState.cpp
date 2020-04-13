#include "SchieldShotBaseState.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/Schield/Shot/SchieldShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss
{
    void SchieldShotBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }

    void SchieldShotBaseState::update(double dt)
    {
        m_body->update(dt);
        // 画面外判定
        if (!m_actor->getModule<Camera>()->inRoom(m_actor->getColliderCircle())) {
            m_actor->destroy();
        }
    }

    void SchieldShotBaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const Receiver&) {
            // 当たって消える
            m_actor->destroy();
        });
    }

    void SchieldShotBaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }

}
