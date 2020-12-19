#include "AttackCrossState.hpp"
#include "WaitState.hpp"

#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/Enemy/Schield/Shot/ShotActor.hpp>

namespace abyss::Actor::Enemy::Schield
{
    AttackCrossState::AttackCrossState()
    {}
    Task<> AttackCrossState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::TimeSec, true);

        m_transitionToWait = ActorUtils::CreateTimer(*m_pActor, Param::View::TransitionTimeSec, false);
        co_return;

    }
    void AttackCrossState::update()
    {
        if (m_timer.reachedZero() && !m_transitionToWait.isRunning()) {
            m_transitionToWait.start();
        }
        if (m_transitionToWait.reachedZero()) {
            this->changeState<WaitState>();
        }
        if (!m_isAttack && m_timer.progress0_1() >= 0.5) {
            m_isAttack = true;
            const auto& pos = m_body->getPos();
            m_pActor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ -34, -25 }, s3d::Vec2{ -1, -1 });
            m_pActor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ 34, -25 }, s3d::Vec2{ 1, -1 });
        }
    }

    void AttackCrossState::draw() const
    {
        if (m_transitionToWait.isStarted()) {
            (*m_view)->drawToWait(m_transitionToWait.progress0_1());
        } else {
            (*m_view)->drawAttackCross();
        }
    }
}
