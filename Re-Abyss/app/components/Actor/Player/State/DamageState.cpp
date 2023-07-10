#include <abyss/components/Actor/Player/State/DamageState.hpp>
#include <abyss/components/Actor/Player/State/SwimState.hpp>
#include <abyss/components/Actor/Player/SeDef.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/views/Actor/Player/PlayerVM.hpp>
#include <abyss/params/Actor/Player/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    DamageState::DamageState(const s3d::Vec2& velocity):
        m_velocity(velocity)
    {}
    void DamageState::start()
    {
        m_motion->set(Motion::Damage);

        BaseState::start();
        m_audio->play(SeDef::Damage);

        auto nextForward = m_body->getForward();
        if (m_velocity.x > 0) {
            nextForward = Forward::Left();
        } else if (m_velocity.x < 0) {
            nextForward = Forward::Right();
        }

        m_body
            ->setAccelX(0)
            .setMaxVelocityY(Body::DefaultMaxVelocityY)
            .setForward(nextForward);

        const Vec2& knockBackSpeed = Param::Damage::KnockBackSpeed;

        const Vec2 velocity{ 
            nextForward.signH() *  -knockBackSpeed.x,
            -knockBackSpeed.y
        };
        m_body->setVelocity(velocity);
    }
    Fiber<> DamageState::updateAsync()
    {
        // 一定時間待機
        co_await BehaviorUtil::WaitForSeconds(m_pActor, Param::Damage::TimeSec);

        // 泳ぎに戻る
        this->changeState<SwimState>();
    }
    void DamageState::update()
    {
    }
}
