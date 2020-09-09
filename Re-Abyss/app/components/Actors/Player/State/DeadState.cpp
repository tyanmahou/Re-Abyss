#include "DeadState.hpp"
#include <abyss/components/Actors/utils/ActorUtils.hpp>
#include <abyss/models/Actors/Commons/FallCheckerModel.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>

#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/Sound/Sound.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    void DeadState::onMove(double dt)
    {
        this->m_body->update(dt);
    }

    void DeadState::start()
    {
        BaseState::start();
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
            .setMaxVelocityY(BodyModel::DefaultMaxVelocityY);

        if (!m_pActor->find<FallCheckerModel>()->isFall()) {
            const Vec2& knockBackSpeed = Param::Dead::KnockBackSpeed;

            const Vec2 velocity{
                m_body->getForward() * -knockBackSpeed.x,
                -knockBackSpeed.y
            };
            m_body->setVelocity(velocity);
        }
    }

    void DeadState::update(double dt)
    {
        this->onMove(dt);
    }

    void DeadState::onDraw(const PlayerVM& view) const
    {
        view.drawStateDamage();
    }

    void DeadState::onCollisionStay([[maybe_unused]]IActor* col)
    {}

    DeadState::DeadState()
    {}

}
