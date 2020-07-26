#include "AttackState.hpp"
#include "WaitState.hpp"

#include <abyss/controllers/World/World.hpp>
#include <abyss/controllers/Actors/Enemy/CaptainTako/Shot/ShotActor.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>
#include <abyss/models/Actors/utils/ActorUtils.hpp>

namespace abyss::CaptainTako
{
    using namespace std::literals;

    AttackState::AttackState():
        m_attackCount(Param::Attack::AttackCount)
    {}
    void AttackState::start()
    {
        m_intervalTimer = ActorUtils::CreateTimer(*m_pActor, Param::Attack::IntervalTimeSec, false);
    }
    void AttackState::update([[maybe_unused]]double dt)
    {
        if (m_intervalTimer.reachedZero() || !m_intervalTimer.isRunning()) {
            constexpr s3d::Vec2 offset{ -9, 4 };
            const s3d::Vec2 fixedOffset{ 
                m_body->isForward(Forward::Left) ? offset.x : -offset.x, 
                offset.y
            };
            auto pos =  m_body->getPos() + fixedOffset;
            m_pActor->getModule<World>()->create<Shot::ShotActor>(pos, m_body->getForward());
            m_intervalTimer.restart();
            if (++m_currentAttackCount >= m_attackCount) {
                this->changeState<WaitState>();
            }
        }
    }

    void AttackState::draw() const
    {
        const double chargeTime = static_cast<double>(m_currentAttackCount) / static_cast<double>(m_attackCount);
        (*m_view)->drawCharge(chargeTime);
    }
}
