#include "BaseState.hpp"
#include <abyss/modules/System/System.hpp>
#include <abyss/components/Actor/Commons/AudioSource.hpp>

namespace abyss::Actor::Player::Shot
{
    void BaseState::setup()
    {
        m_shot = this->m_pActor->find<PlayerShot>().get();
        m_collider = this->m_pActor->find<Collider>().get();
        m_view = this->m_pActor->find<ViewCtrl<ShotVM>>().get();
    }

    Task<> BaseState::start()
    {
        if (m_shot->isBig()) {
            m_pActor->find<AudioSource>()->playAt(U"ShotBig");
        } else if (m_shot->isMedium()) {
            m_pActor->find<AudioSource>()->playAt(U"ShotMedium");
        } else {
            m_pActor->find<AudioSource>()->playAt(U"ShotSmall");
        }
        co_return;
    }

    void BaseState::update()
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
