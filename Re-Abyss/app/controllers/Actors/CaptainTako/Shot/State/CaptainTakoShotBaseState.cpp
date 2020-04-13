#include "CaptainTakoShotBaseState.hpp"

#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/CaptainTako/Shot/CaptainTakoShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss
{
    void CaptainTakoShotBaseState::setup()
    {
        m_body = this->binded<BodyModel>();
    }

    void CaptainTakoShotBaseState::start()
    {

    }

    void CaptainTakoShotBaseState::update(double dt)
    {
        m_body->update(dt);
        // 画面外判定
        if (!m_actor->getModule<Camera>()->inRoom(m_actor->getColliderCircle())) {
            m_actor->destroy();
        }
    }

    void CaptainTakoShotBaseState::onCollisionStay(ICollider* col)
    {
        col->accept([this](const Receiver&) {
            // 当たって消える
            m_actor->destroy();
        });
    }

    void CaptainTakoShotBaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }

}
