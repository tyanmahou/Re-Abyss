#include "AttackCrossState.hpp"
#include <abyss/views/Actors/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Schield/Param.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/Schield/Shot/ShotActor.hpp>

namespace abyss::Schield
{
    AttackCrossState::AttackCrossState()
    {}
    void AttackCrossState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::TimeSec, true);

        m_transitionToWait = ActorUtils::CreateTimer(*m_pActor, Param::View::TransitionTimeSec, false);

    }
    void AttackCrossState::update(double dt)
    {
        BaseState::update(dt);

        if (m_timer.reachedZero() && !m_transitionToWait.isRunning()) {
            m_transitionToWait.start();
        }
        if (m_transitionToWait.reachedZero()) {
            this->changeState(State::Wait);
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
            m_pActor->getBindedView()->drawToWait(m_transitionToWait.progress0_1());
        } else {
            m_pActor->getBindedView()->drawAttackCross();
        }
    }
}
