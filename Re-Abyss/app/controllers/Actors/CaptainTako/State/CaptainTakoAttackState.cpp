#include "CaptainTakoAttackState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/controllers/World/World.hpp>
#include <abyss/views/Actors/CaptainTako/CpatainTakoVM.hpp>
#include <abyss/controllers/Actors/CaptainTako/Shot/CaptainTakoShotActor.hpp>

namespace abyss
{
    using namespace std::literals;

    CaptainTakoAttackState::CaptainTakoAttackState():
        m_intervalTimer(0.1, false, WorldTime::TimeMicroSec)
    {}

    void CaptainTakoAttackState::update(double dt)
    {
        if (m_intervalTimer.reachedZero() || !m_intervalTimer.isRunning()) {
            constexpr s3d::Vec2 offset{ -9, 4 };
            const s3d::Vec2 fixedOffset{ 
                m_body->isForward(Forward::Left) ? offset.x : -offset.x, 
                offset.y
            };
            auto pos =  m_body->getPos() + fixedOffset;
            this->m_actor->getWorld()->create<CaptainTakoShotActor>(pos, m_body->getForward());
            m_intervalTimer.restart(0.1s);
            if (++m_currentAttackCount >= m_attackCount) {
                this->changeState(CaptainTakoActor::State::Wait);
            }
        }
        CaptainTakoBaseState::update(dt);
    }

    void CaptainTakoAttackState::draw() const
    {
        m_actor->getBindedView()->drawCharge(static_cast<double>(m_currentAttackCount) / static_cast<double>(m_attackCount));
    }
}
