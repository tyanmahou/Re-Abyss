#include "BaseState.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss::Player::Shot
{
    void BaseState::setup()
    {    
        m_body = this->m_pActor->findComponent<BodyModel>().get();
        m_shot = this->m_pActor->findComponent<PlayerShotModel>().get();
    }

    void BaseState::start()
    {
        m_pActor->getBindedView()->addShotFiringEffect();
    }

    void BaseState::update(double dt)
    {
        m_body->update(dt);
        // 画面外判定
        if (!m_pActor->getModule<Camera>()->inRoom(m_pActor->getColliderCircle())) {
            m_pActor->destroy();
        }
    }

    void BaseState::onCollisionStay(IActor * col)
    {
        col->accept([this](const Receiver&) {
            if (!m_shot->isBig()) {

                // 当たって消える
                m_pActor->destroy();
            }
        });
    }

    void BaseState::draw() const
    {
        m_pActor->getBindedView()->draw();
    }
}
