#include "AttackState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/controllers/Actors/CaptainTako/Shot/ShotActor.hpp>
#include <abyss/params/Actors/CaptainTako/Param.hpp>
namespace abyss::CaptainTako
{
    using namespace std::literals;

    AttackState::AttackState():
        m_intervalTimer(Param::Attack::IntervalTimeSec, false, WorldTime::TimeMicroSec),
        m_attackCount(Param::Attack::AttackCount)
    {}

    void AttackState::update(double dt)
    {
        if (m_intervalTimer.reachedZero() || !m_intervalTimer.isRunning()) {
            constexpr s3d::Vec2 offset{ -9, 4 };
            const s3d::Vec2 fixedOffset{ 
                m_body->isForward(Forward::Left) ? offset.x : -offset.x, 
                offset.y
            };
            auto pos =  m_body->getPos() + fixedOffset;
            this->m_actor->getModule<World>()->create<Shot::ShotActor>(pos, m_body->getForward());
            m_intervalTimer.restart();
            if (++m_currentAttackCount >= m_attackCount) {
                this->changeState(State::Wait);
            }
        }
        BaseState::update(dt);
    }

    void AttackState::draw() const
    {
        m_actor->getBindedView()->drawCharge(static_cast<double>(m_currentAttackCount) / static_cast<double>(m_attackCount));
    }
}
