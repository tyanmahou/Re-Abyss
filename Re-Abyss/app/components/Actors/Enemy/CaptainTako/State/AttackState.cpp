#include "AttackState.hpp"
#include "WaitState.hpp"

#include <abyss/modules/World/World.hpp>
#include <abyss/components/Actors/Enemy/CaptainTako/Shot/Builder.hpp>
#include <abyss/params/Actors/Enemy/CaptainTako/Param.hpp>
#include <abyss/components/Actors/utils/BehaviorUtil.hpp>

namespace abyss::Actor::Enemy::CaptainTako
{
    using namespace std::literals;

    AttackState::AttackState():
        m_attackCount(Param::Attack::AttackCount)
    {}
    Task<> AttackState::start()
    {
        while (true) {
            // ショット
            constexpr s3d::Vec2 offset{ -9, 4 };
            const s3d::Vec2 fixedOffset{
                m_body->isForward(Forward::Left) ? offset.x : -offset.x,
                offset.y
            };
            auto pos = m_body->getPos() + fixedOffset;
            m_pActor->getModule<World>()->create<Shot::Builder>(pos, m_body->getForward());

            if (++m_currentAttackCount >= m_attackCount) {
                break;
            }
            co_yield BehaviorUtils::WaitForSeconds(m_pActor, Param::Attack::IntervalTimeSec);
        }
        this->changeState<WaitState>();
        co_return;
    }
    void AttackState::update()
    {
    }

    void AttackState::draw() const
    {
        const double chargeTime = static_cast<double>(m_attackCount - m_currentAttackCount) / static_cast<double>(m_attackCount);
        (*m_view)->drawCharge(chargeTime);
    }
}
