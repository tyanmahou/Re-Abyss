#include "AttackPlusState.hpp"
#include "AttackCrossState.hpp"

#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/components/Actors/Enemy/Schield/Shot/Builder.hpp>
#include <abyss/modules/System/System.hpp>

namespace abyss::Actor::Enemy::Schield
{
    AttackPlusState::AttackPlusState()
    {}
    Task<> AttackPlusState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::TimeSec, false);

        m_transitionToAttackPlus = ActorUtils::CreateTimer(*m_pActor, Param::View::TransitionTimeSec, true);
        m_transitionToAttackCross = ActorUtils::CreateTimer(*m_pActor, Param::View::TransitionTimeSec, false);
        co_return;

    }
    void AttackPlusState::update()
    {
        if (m_transitionToAttackPlus.reachedZero() && !m_timer.isRunning()) {
            m_timer.start();
        }
        if (m_timer.reachedZero()&& !m_transitionToAttackCross.isRunning()) {
            m_transitionToAttackCross.start();
        }
        if (m_transitionToAttackCross.reachedZero()) {
            this->changeState<AttackCrossState>();
        }
        if (!m_isAttack && m_timer.progress0_1() >= 0.5) {
            m_isAttack = true;
            const auto& pos = m_body->getPos();
            m_pActor->getModule<World>()->create<Shot::Builder>(pos + s3d::Vec2{ -55, 10 }, s3d::Vec2{-1, 0});
            m_pActor->getModule<World>()->create<Shot::Builder>(pos + s3d::Vec2{ 55, 10 }, s3d::Vec2{ 1, 0 });
            m_pActor->getModule<World>()->create<Shot::Builder>(pos + s3d::Vec2{ 0, -27 }, s3d::Vec2{ 0, -1 });
        }
    }

    void AttackPlusState::draw() const
    {
        if (m_transitionToAttackCross.isRunning()) {
            (*m_view)->drawToAttackCross(m_transitionToAttackCross.progress0_1());
        } else {
            (*m_view)->drawToAttackPlus(m_transitionToAttackPlus.progress0_1());
        }
    }
}
