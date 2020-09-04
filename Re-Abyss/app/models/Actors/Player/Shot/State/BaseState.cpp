#include "BaseState.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>

namespace abyss::Actor::Player::Shot
{
    void BaseState::setup()
    {
        m_shot = this->m_pActor->find<PlayerShotModel>().get();
        m_collider = this->m_pActor->find<ColliderModel>().get();
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

    void BaseState::update([[maybe_unused]]double dt)
    {
        // 画面外判定
        if (!m_pActor->getModule<Camera>()->inScreen(m_collider->getColliderCircle())) {
            m_pActor->destroy();
        }
    }

    void BaseState::draw() const
    {
        (*m_view)->draw();
    }
}
