#include "AttackPlusState.hpp"
#include "AttackCrossState.hpp"

#include <abyss/params/Actors/Enemy/Schield/Param.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/Enemy/Schield/Shot/ShotActor.hpp>

namespace abyss::Schield
{
    AttackPlusState::AttackPlusState()
    {}
    void AttackPlusState::start()
    {
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::TimeSec, false);

        m_transitionToAttackPlus = ActorUtils::CreateTimer(*m_pActor, Param::View::TransitionTimeSec, true);
        m_transitionToAttackCross = ActorUtils::CreateTimer(*m_pActor, Param::View::TransitionTimeSec, false);

    }
    void AttackPlusState::update([[maybe_unused]] double dt)
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
            m_pActor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ -55, 10 }, s3d::Vec2{-1, 0});
            m_pActor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ 55, 10 }, s3d::Vec2{ 1, 0 });
            m_pActor->getModule<World>()->create<Shot::ShotActor>(pos + s3d::Vec2{ 0, -27 }, s3d::Vec2{ 0, -1 });
        }

        // view更新
        if (m_transitionToAttackCross.isRunning()) {
            m_draw
                ->setTransitionTime(m_transitionToAttackCross.progress0_1())
                .request(DrawModel::Kind::ToAttackCross);
        } else {
            m_draw
                ->setTransitionTime(m_transitionToAttackPlus.progress0_1())
                .request(DrawModel::Kind::ToAttackPlus);
        }
    }
}
