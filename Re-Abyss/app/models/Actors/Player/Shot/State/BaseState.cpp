#include "BaseState.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/views/Actors/Player/Shot/ShotVM.hpp>
#include <abyss/commons/ActInclude.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>

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
        if (m_shot->isBig()) {
            m_pActor->find<AudioSourceModel>()->playAt(U"Player/Shot/shot3.ogg");
        } else if (m_shot->isMedium()) {
            m_pActor->find<AudioSourceModel>()->playAt(U"Player/Shot/shot2.ogg");
        } else {
            m_pActor->find<AudioSourceModel>()->playAt(U"Player/Shot/shot.ogg");
        }
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
