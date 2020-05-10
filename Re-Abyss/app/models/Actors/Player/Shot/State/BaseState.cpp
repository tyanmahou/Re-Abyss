#include "BaseState.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>

namespace abyss::Player::Shot
{
    void BaseState::setup()
    {    
        m_body = this->m_pActor->find<BodyModel>().get();
        m_shot = this->m_pActor->find<PlayerShotModel>().get();
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

    void BaseState::draw() const
    {
        m_pActor->getBindedView()->draw();
    }
}
