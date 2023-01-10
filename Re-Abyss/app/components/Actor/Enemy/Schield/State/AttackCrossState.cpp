#include <abyss/components/Actor/Enemy/Schield/State/AttackCrossState.hpp>
#include <abyss/components/Actor/Enemy/Schield/State/WaitState.hpp>

#include <abyss/params/Actor/Enemy/Schield/Param.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/components/Actor/Enemy/Schield/Shot/Builder.hpp>

namespace abyss::Actor::Enemy::Schield
{
    AttackCrossState::AttackCrossState():
        m_timer(Param::Attack::TimeSec),
        m_transitionToWait(Param::View::TransitionTimeSec)
    {}
    void AttackCrossState::start()
    {
        m_motion->set(Motion::AttackCross);
    }
    void AttackCrossState::update()
    {
        double dt = m_pActor->deltaTime();

        m_timer.update(dt);
        if (m_timer.isEnd()) {
            m_transitionToWait.update(dt);
        }
        if (m_transitionToWait.isEnd()) {
            this->changeState<WaitState>();
        }
        if (!m_isAttack && m_timer.rate() >= 0.5) {
            m_isAttack = true;
            const auto& pos = m_body->getPos();
            m_pActor->getModule<Actors>()->create<Shot::Builder>(pos + s3d::Vec2{ -34, -25 }, s3d::Vec2{ -1, -1 });
            m_pActor->getModule<Actors>()->create<Shot::Builder>(pos + s3d::Vec2{ 34, -25 }, s3d::Vec2{ 1, -1 });
        }

        if (m_transitionToWait.isRunning()) {
            m_motion->set(Motion::ToWait).setAnimeTime(m_transitionToWait.rate());
        } else {
            m_motion->set(Motion::AttackCross);
        }
    }
}
