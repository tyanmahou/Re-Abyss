#include "PlayerShotBaseState.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/Player/Shot/PlayerShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss
{
    void PlayerShotBaseState::setup()
    {    
        m_body = this->binded<BodyModel>();
        m_shot = this->binded<PlayerShotModel>();
    }

    void PlayerShotBaseState::start()
    {
        m_actor->getBindedView()->addShotFiringEffect();
    }

    void PlayerShotBaseState::update(double dt)
    {
        m_body->update(dt);
        // 画面外判定
        if (!ActionSystem::Camera()->inRoom(m_actor->getColliderCircle())) {
            m_actor->destroy();
        }
    }

    void PlayerShotBaseState::onCollisionStay(ICollider * col)
    {
        col->accept([this](const Receiver&) {
            if (!m_shot->isBig()) {

                // 当たって消える
                m_actor->destroy();
            }
        });
    }

    void PlayerShotBaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}
