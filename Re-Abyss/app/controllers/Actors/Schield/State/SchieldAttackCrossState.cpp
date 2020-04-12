#include "SchieldAttackCrossState.hpp"
#include <abyss/views/Actors/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Schield/SchieldParam.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/Schield/Shot/SchieldShotActor.hpp>

namespace abyss
{
    SchieldAttackCrossState::SchieldAttackCrossState() :
        m_timer(SchieldParam::Attack::TimeSec, true, WorldTime::TimeMicroSec),
        m_transitionToWait(SchieldParam::View::TransitionTimeSec, false, WorldTime::TimeMicroSec)
    {}
    void SchieldAttackCrossState::update(double dt)
    {
        SchieldBaseState::update(dt);

        if (m_timer.reachedZero() && !m_transitionToWait.isRunning()) {
            m_transitionToWait.start();
        }
        if (m_transitionToWait.reachedZero()) {
            this->changeState(SchieldActor::State::Wait);
        }
        if (!m_isAttack && m_timer.progress0_1() >= 0.5) {
            m_isAttack = true;
            const auto& pos = m_body->getPos();
            m_actor->getWorld()->create<SchieldShotActor>(pos + s3d::Vec2{ -34, -25 }, s3d::Vec2{ -1, -1 });
            m_actor->getWorld()->create<SchieldShotActor>(pos + s3d::Vec2{ 34, -25 }, s3d::Vec2{ 1, -1 });
        }

    }

    void SchieldAttackCrossState::draw() const
    {
        if (m_transitionToWait.isStarted()) {
            m_actor->getBindedView()->drawToWait(m_transitionToWait.progress0_1());
        } else {
            m_actor->getBindedView()->drawAttackCross();
        }
    }
}
