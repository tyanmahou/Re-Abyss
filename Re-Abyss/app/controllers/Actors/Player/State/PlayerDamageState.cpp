#include "PlayerDamageState.hpp"
#include <abyss/controllers/World/WorldTime.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/PlayerParam.hpp>

namespace abyss
{
    PlayerDamageState::PlayerDamageState():
        m_damageTimer(0.5s, true, WorldTime::TimeMicroSec)
    {}
    void PlayerDamageState::onMove(double dt)
    {
        this->m_body->update(dt);
    }
    void PlayerDamageState::start()
    {
        m_body
            ->setAccelX(0)
            .setMaxVelocityY(BodyModel::DefaultMaxVelocityY);

        const Vec2& knockBackSpeed = PlayerParam::Damage::KnockBackSpeed;

        const Vec2 velocity{ 
            m_body->getForward() *  -knockBackSpeed.x,
            -knockBackSpeed.y
        };
        m_body->setVelocity(velocity);
    }
    void PlayerDamageState::update(double dt)
    {
        this->onMove(dt);
        if (m_damageTimer.reachedZero()) {
            this->changeState(PlayerActor::State::Swim);
        }
    }
    void PlayerDamageState::onDraw(const PlayerVM& view) const
    {
        view.drawStateDamage();
    }
}
