#include <abyss/components/Actor/Player/Shot/State/BaseState.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/components/Actor/Common/AudioSource.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Player/SeDef.hpp>

namespace abyss::Actor::Player::Shot
{
    void BaseState::onCache()
    {
        m_shot = this->m_pActor->find<PlayerShot>().get();
        m_collider = this->m_pActor->find<Collider>()->main<MainCollider>().get();
    }

    void BaseState::start()
    {
        if (m_shot->isBig()) {
            m_pActor->find<AudioSource>()->playAt(SeDef::ShotBig);
        } else if (m_shot->isMedium()) {
            m_pActor->find<AudioSource>()->playAt(SeDef::ShotMedium);
        } else {
            m_pActor->find<AudioSource>()->playAt(SeDef::ShotSmall);
        }
    }

    void BaseState::update()
    {
        // 画面外判定
        if (!m_pActor->getModule<Camera>()->inScreen(m_collider->getColliderCircle())) {
            m_pActor->destroy();
        }
    }
}
