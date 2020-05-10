#include "DamageState.hpp"
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/Param.hpp>

namespace abyss::Player
{
    DamageState::DamageState()
    {}
    void DamageState::onMove(double dt)
    {
        this->m_body->update(dt);
    }
    void DamageState::start()
    {
        m_damageTimer = ActorUtils::CreateTimer(*m_pActor, Param::Damage::TimeSec);
        m_body
            ->setAccelX(0)
            .setMaxVelocityY(BodyModel::DefaultMaxVelocityY);

        const Vec2& knockBackSpeed = Param::Damage::KnockBackSpeed;

        const Vec2 velocity{ 
            m_body->getForward() *  -knockBackSpeed.x,
            -knockBackSpeed.y
        };
        m_body->setVelocity(velocity);
    }
    void DamageState::update(double dt)
    {
        this->onMove(dt);
        if (m_damageTimer.reachedZero()) {
            this->changeState(State::Swim);
        }
    }
    void DamageState::onDraw(const PlayerVM& view) const
    {
        view.drawStateDamage();
    }
}
