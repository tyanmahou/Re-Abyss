#include "TalkState.hpp"
#include <abyss/components/Actor/Commons/CustomCollider.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    TalkState::TalkState(const Ref<ILocator>& pTargetLocator):
        m_pTargetLocator(pTargetLocator)
    {
    }

    void TalkState::onLanding()
    {
        if (m_motion == Motion::Float && m_body->getVelocity().x == 0) {
            m_motion = Motion::Stay;
        } else if (m_motion == Motion::Swim && Abs(m_body->getVelocity().x) > 90) {
            m_motion = Motion::Run;
        }
    }

    void TalkState::start()
    {
        Vec2 vecPrev = m_body->getVelocity();
        BaseState::start();
        m_body->setVelocity(Vec2{vecPrev.x / 2, vecPrev.y});

        // ダメージ受けない
        m_damageCtrl->setActive(false);
        m_pActor->find<CustomCollider>()->setActive(false);
    }
    void TalkState::end()
    {
        m_pActor->find<CustomCollider>()->setActive(true);
    }
    void TalkState::update()
    {
        if (m_pTargetLocator) {
            auto toTarget = m_pTargetLocator->getCenterPos() - m_body->getCenterPos();
            if (toTarget.x >= 0) {
                m_body->setForward(Forward::Right);
            } else {
                m_body->setForward(Forward::Left);
            }
        }
        m_motion = Motion::Float;
        if (m_body->getVelocity().y > Body::DefaultMaxVelocityY) {
            m_motion = Motion::Dive;
        }
    }
    void TalkState::lastUpdate()
    {
        BaseState::lastUpdate();
    }
    void TalkState::onDraw(const PlayerVM & view) const
    {
        switch (m_motion) {
        case Motion::Stay: return view.drawStateStay();
        case Motion::Swim: return view.drawStateSwim();
        case Motion::Run: return view.drawStateRun();
        case Motion::Float: return view.drawStateFloat();
        case Motion::Dive: return view.drawStateDive();
        case Motion::Ladder: return view.drawStateLadder();
        default:
            break;
        }
    }
}
