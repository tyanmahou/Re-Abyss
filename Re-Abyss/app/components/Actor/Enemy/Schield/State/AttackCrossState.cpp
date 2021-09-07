#include "AttackCrossState.hpp"
#include "WaitState.hpp"

#include <abyss/params/Actor/Enemy/Schield/Param.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actor/Enemy/Schield/Shot/Builder.hpp>

namespace abyss::Actor::Enemy::Schield
{
    AttackCrossState::AttackCrossState()
    {}
    void AttackCrossState::start()
    {
        m_motion->set(Motion::AttackCross);
        m_timer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::TimeSec, true);

        m_transitionToWait = ActorUtils::CreateTimer(*m_pActor, Param::View::TransitionTimeSec, false);
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
            m_pActor->getModule<World>()->create<Shot::Builder>(pos + s3d::Vec2{ -34, -25 }, s3d::Vec2{ -1, -1 });
            m_pActor->getModule<World>()->create<Shot::Builder>(pos + s3d::Vec2{ 34, -25 }, s3d::Vec2{ 1, -1 });
        }

        if (m_transitionToWait.isStarted()) {
            m_motion->set(Motion::ToWait).setAnimeTime(m_transitionToWait.progress0_1());
        } else {
            m_motion->set(Motion::AttackCross);
        }
    }
}
