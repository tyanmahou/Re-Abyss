#include "AttackCrossState.hpp"
#include <abyss/views/Actors/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Schield/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/Schield/Shot/ShotActor.hpp>

namespace abyss::Schield
{
    AttackCrossState::AttackCrossState() :
        m_timer(Param::Attack::TimeSec, true, WorldTime::TimeMicroSec),
        m_transitionToWait(Param::View::TransitionTimeSec, false, WorldTime::TimeMicroSec)
    {}
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
            m_actor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ -34, -25 }, s3d::Vec2{ -1, -1 });
            m_actor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ 34, -25 }, s3d::Vec2{ 1, -1 });
        }

    }

    void AttackCrossState::draw() const
    {
        if (m_transitionToWait.isStarted()) {
            m_actor->getBindedView()->drawToWait(m_transitionToWait.progress0_1());
        } else {
            m_actor->getBindedView()->drawAttackCross();
        }
    }
}
