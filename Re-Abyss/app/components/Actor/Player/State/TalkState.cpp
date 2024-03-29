#include <abyss/components/Actor/Player/State/TalkState.hpp>
#include <abyss/components/Actor/utils/StatePriority.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    void TalkState::Change(ActorObj* pActor, const Ref<ILocator>& pTargetLocator)
    {
        pActor->find<StateCtrl>()->changeState<TalkState, StatePriority::Event>(pTargetLocator);
    }
    TalkState::TalkState(const Ref<ILocator>& pTargetLocator):
        m_pTargetLocator(pTargetLocator)
    {
    }

    void TalkState::onLanding()
    {
        if (m_motion->is(Motion::Float) && m_body->getVelocity().x == 0) {
            m_motion->set(Motion::Stay);
        } else if (m_motion->is(Motion::Swim) && Abs(m_body->getVelocity().x) > 90) {
            m_motion->set(Motion::Run);
        }
    }

    void TalkState::start()
    {
        m_motion->set(Motion::Stay);

        Vec2 vecPrev = m_body->getVelocity();
        BaseState::start();
        m_body->setVelocity(Vec2{vecPrev.x / 2, vecPrev.y});

        // ダメージ受けない
        m_damageCtrl->setActive(false);
        m_colCtrl->setActive(false);
    }
    void TalkState::end()
    {
        m_colCtrl->setActive(true);
    }
    void TalkState::update()
    {
        if (m_pTargetLocator) {
            auto toTarget = m_pTargetLocator->getCenterPos() - m_body->getCenterPos();
            if (toTarget.x >= 0) {
                m_body->setForward(Forward::Right());
            } else {
                m_body->setForward(Forward::Left());
            }
        }
        m_motion->set(Motion::Float);
        if (m_body->getVelocity().y > Body::DefaultMaxVelocityY) {
            m_motion->set(Motion::Dive);
        }
    }
    void TalkState::lastUpdate()
    {
        BaseState::lastUpdate();
    }
}
