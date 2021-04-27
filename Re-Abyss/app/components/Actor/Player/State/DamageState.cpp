#include "DamageState.hpp"
#include "SwimState.hpp"
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <abyss/params/Actor/Player/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    DamageState::DamageState(const s3d::Vec2& velocity):
        m_velocity(velocity)
    {}
    Task<> DamageState::start()
    {
        co_yield BaseState::start();
        m_pActor->find<AudioSource>()->play(U"Damage");

        auto nextForward = m_body->getForward();
        if (m_velocity.x > 0) {
            nextForward = Forward::Left;
        } else if (m_velocity.x < 0) {
            nextForward = Forward::Right;
        }

        m_body
            ->setAccelX(0)
            .setMaxVelocityY(Body::DefaultMaxVelocityY)
            .setForward(nextForward);

        const Vec2& knockBackSpeed = Param::Damage::KnockBackSpeed;

        const Vec2 velocity{ 
            nextForward *  -knockBackSpeed.x,
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
