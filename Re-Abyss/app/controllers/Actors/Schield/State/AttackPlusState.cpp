#include "AttackPlusState.hpp"
#include <abyss/views/Actors/Schield/SchieldVM.hpp>
#include <abyss/params/Actors/Schield/Param.hpp>
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/controllers/Actors/Schield/Shot/ShotActor.hpp>

namespace abyss::Schield
{
    AttackPlusState::AttackPlusState() :
        m_timer(Param::Attack::TimeSec, false, WorldTime::TimeMicroSec),
        m_transitionToAttackPlus(Param::View::TransitionTimeSec, true, WorldTime::TimeMicroSec),
        m_transitionToAttackCross(Param::View::TransitionTimeSec, false, WorldTime::TimeMicroSec)
    {}
    void AttackPlusState::update(double dt)
    {
        BaseState::update(dt);
        if (m_transitionToAttackPlus.reachedZero() && !m_timer.isRunning()) {
            m_timer.start();
        }
        if (m_timer.reachedZero()&& !m_transitionToAttackCross.isRunning()) {
            m_transitionToAttackCross.start();
        }
        if (m_transitionToAttackCross.reachedZero()) {
            this->changeState(SchieldActor::State::AttackCross);
        }
        if (!m_isAttack && m_timer.progress0_1() >= 0.5) {
            m_isAttack = true;
            const auto& pos = m_body->getPos();
            m_actor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ -55, 10 }, s3d::Vec2{-1, 0});
            m_actor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ 55, 10 }, s3d::Vec2{ 1, 0 });
            m_actor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ 0, -27 }, s3d::Vec2{ 0, -1 });
        }
    }

    void AttackPlusState::draw() const
    {
        if (m_transitionToAttackCross.isRunning()) {
            m_actor->getBindedView()->drawToAttackCross(m_transitionToAttackCross.progress0_1());
        } else {
            m_actor->getBindedView()->drawToAttackPlus(m_transitionToAttackPlus.progress0_1());
        }
    }
}
