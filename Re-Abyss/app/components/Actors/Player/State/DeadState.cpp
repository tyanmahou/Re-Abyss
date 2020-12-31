#include "DeadState.hpp"
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/components/Actors/Commons/FallChecker.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>

#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    Task<> DeadState::start()
    {
        co_yield BaseState::start();
        // 無敵時間をなしに
        m_hp->setInvincibleTime(0);

        // サウンド停止
        m_pActor->getModule<Sound>()->stop(0.5s);

        // 地震
        m_pActor->getModule<Camera>()->startQuake(5.0, 0.5);

        m_pActor->find<AudioSource>()->play(U"Dead");

        m_deadTimer = ActorUtils::CreateTimer(*m_pActor, Param::Dead::TimeSec);
        m_body
            ->setAccelX(0)
            .setMaxVelocityY(Body::DefaultMaxVelocityY);

        if (!m_pActor->find<FallChecker>()->isFall()) {
            const Vec2& knockBackSpeed = Param::Dead::KnockBackSpeed;

            const Vec2 velocity{
                m_body->getForward() * -knockBackSpeed.x,
                -knockBackSpeed.y
            };
            m_body->setVelocity(velocity);
        }
        co_return;
    }

    void DeadState::update()
    {
    }

    void DeadState::onDraw(const PlayerVM& view) const
    {
        view.drawStateDamage();
    }

    void DeadState::onPostCollision()
    {}

    DeadState::DeadState()
    {}

}
