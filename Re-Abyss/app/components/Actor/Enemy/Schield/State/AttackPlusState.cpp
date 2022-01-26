#include <abyss/components/Actor/Enemy/Schield/State/AttackPlusState.hpp>
#include <abyss/components/Actor/Enemy/Schield/State/AttackCrossState.hpp>

#include <abyss/params/Actor/Enemy/Schield/Param.hpp>
#include <abyss/components/Actor/Enemy/Schield/Shot/Builder.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/World/World.hpp>

namespace abyss::Actor::Enemy::Schield
{
    AttackPlusState::AttackPlusState():
        m_timer(Param::Attack::TimeSec),
        m_transitionToAttackPlus(Param::View::TransitionTimeSec),
        m_transitionToAttackCross(Param::View::TransitionTimeSec)
    {}
    void AttackPlusState::start()
    {
        m_motion->set(Motion::ToAttackPlus).setAnimeTime(0.0);
    }
    void AttackPlusState::update()
    {
        double dt = m_pActor->deltaTime();

        m_transitionToAttackPlus.update(dt);
        if (m_transitionToAttackPlus.isEnd()) {
            m_timer.update(dt);
        }
        if (m_timer.isEnd()) {
            m_transitionToAttackCross.update(dt);
        }
        if (m_transitionToAttackCross.isEnd()) {
            this->changeState<AttackCrossState>();
        }
        if (!m_isAttack && m_timer.rate() >= 0.5) {
            m_isAttack = true;
            const auto& pos = m_body->getPos();
            m_pActor->getModule<World>()->create<Shot::Builder>(pos + s3d::Vec2{ -55, 10 }, s3d::Vec2{-1, 0});
            m_pActor->getModule<World>()->create<Shot::Builder>(pos + s3d::Vec2{ 55, 10 }, s3d::Vec2{ 1, 0 });
            m_pActor->getModule<World>()->create<Shot::Builder>(pos + s3d::Vec2{ 0, -27 }, s3d::Vec2{ 0, -1 });
        }

        if (m_transitionToAttackCross.isRunning()) {
            m_motion->set(Motion::ToAttackCross).setAnimeTime(m_transitionToAttackCross.rate());
        } else {
            m_motion->set(Motion::ToAttackPlus).setAnimeTime(m_transitionToAttackPlus.rate());
        }
    }
}
