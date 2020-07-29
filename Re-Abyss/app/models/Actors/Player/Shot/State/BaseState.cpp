#include "BaseState.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>

namespace abyss::Player::Shot
{
    void BaseState::setup()
    {    
        m_body = this->m_pActor->find<BodyModel>().get();
        m_shot = this->m_pActor->find<PlayerShotModel>().get();
        m_view = this->m_pActor->find<ViewModel<ShotVM>>().get();
    }

    void BaseState::start()
    {
        (*m_view)->addShotFiringEffect();
        if (m_shot->isBig()) {
            m_pActor->find<AudioSourceModel>()->playAt(U"ShotBig");
        } else if (m_shot->isMedium()) {
            m_pActor->find<AudioSourceModel>()->playAt(U"ShotMedium");
        } else {
            m_pActor->find<AudioSourceModel>()->playAt(U"ShotSmall");
        }
    }

    void BaseState::update(double dt)
    {
        m_body->update(dt);

        auto col = s3d::Circle(m_body->getPos(), m_shot->toRadius());
        // 画面外判定
        if (!m_pActor->getModule<Camera>()->inScreen(m_pActor->getColliderCircle())) {
            m_pActor->destroy();
        }
    }

    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
