#include "DamageState.hpp"
#include "SwimState.hpp"
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    DamageState::DamageState()
    {
    }
    Task<> DamageState::start()
    {
        co_yield BaseState::start();
        m_pActor->find<AudioSource>()->play(U"Damage");

        m_damageTimer = ActorUtils::CreateTimer(*m_pActor, Param::Damage::TimeSec);
        m_body
            ->setAccelX(0)
            .setMaxVelocityY(Body::DefaultMaxVelocityY);

        const Vec2& knockBackSpeed = Param::Damage::KnockBackSpeed;

        const Vec2 velocity{ 
            m_body->getForward() *  -knockBackSpeed.x,
            -knockBackSpeed.y
        };
        m_body->setVelocity(velocity);
        co_return;
    }
    void DamageState::update()
    {
        if (m_damageTimer.reachedZero()) {
            this->changeState<SwimState>();
        }
    }
    void DamageState::onDraw(const PlayerVM& view) const
    {
        view.drawStateDamage();
    }
}
