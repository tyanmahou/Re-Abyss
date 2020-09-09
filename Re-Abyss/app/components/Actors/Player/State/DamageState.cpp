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
    void DamageState::onMove(double dt)
    {
        this->m_body->update(dt);
    }
    void DamageState::start()
    {
        BaseState::start();
        m_pActor->find<AudioSource>()->play(U"Damage");

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
            this->changeState<SwimState>();
        }
    }
    void DamageState::onDraw(const PlayerVM& view) const
    {
        view.drawStateDamage();
    }
}
