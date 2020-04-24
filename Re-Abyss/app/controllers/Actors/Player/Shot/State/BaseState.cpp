#include "BaseState.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss::Player::Shot
{
    void BaseState::setup()
    {    
        m_body = this->binded<BodyModel>();
        m_shot = this->binded<PlayerShotModel>();
    }

    void BaseState::start()
    {
        m_actor->getBindedView()->addShotFiringEffect();
    }

    void BaseState::update(double dt)
    {
        m_body->update(dt);
        // 画面外判定
        if (!m_actor->getModule<Camera>()->inRoom(m_actor->getColliderCircle())) {
            m_actor->destroy();
        }
    }

    void BaseState::onCollisionStay(ICollider * col)
    {
        col->accept([this](const Receiver&) {
            if (!m_shot->isBig()) {

                // 当たって消える
                m_actor->destroy();
            }
        });
    }

    void BaseState::draw() const
    {
        m_actor->getBindedView()->draw();
    }
}
