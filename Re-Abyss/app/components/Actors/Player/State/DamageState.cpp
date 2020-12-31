#include "DamageState.hpp"
#include "SwimState.hpp"
#include <abyss/components/Actors/utils/BehaviorUtil.hpp>
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

       m_body
            ->setAccelX(0)
            .setMaxVelocityY(Body::DefaultMaxVelocityY);

        const Vec2& knockBackSpeed = Param::Damage::KnockBackSpeed;

        const Vec2 velocity{ 
            m_body->getForward() *  -knockBackSpeed.x,
            -knockBackSpeed.y
        };
        m_body->setVelocity(velocity);

        // 一定時間待機
        co_yield BehaviorUtils::WaitForSeconds(m_pActor, Param::Damage::TimeSec);

        // 泳ぎに戻る
        this->changeState<SwimState>();
        co_return;
    }
    void DamageState::update()
    {
    }
    void DamageState::onDraw(const PlayerVM& view) const
    {
        view.drawStateDamage();
    }
}
