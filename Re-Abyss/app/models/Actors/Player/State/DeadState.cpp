#include "DeadState.hpp"
#include <abyss/models/Actors/utils/ActorUtils.hpp>
#include <abyss/params/Actors/Player/Param.hpp>
#include <abyss/views/Actors/Player/PlayerVM.hpp>

#include <abyss/controllers/Event/Events.hpp>
#include <abyss/controllers/Event/GameRestart/GameRestart.hpp>
#include <abyss/controllers/Sound/Sound.hpp>

namespace abyss::Player
{
    void DeadState::onMove(double dt)
    {
        this->m_body->update(dt);
    }

    void DeadState::start()
    {
        BaseState::start();

        // サウンド停止
        m_pActor->getModule<Sound>()->stop(0.5s);

        m_pActor->find<AudioSourceModel>()->play(U"Dead");

        m_deadTimer = ActorUtils::CreateTimer(*m_pActor, Param::Dead::TimeSec);
        m_body
            ->setAccelX(0)
            .setMaxVelocityY(BodyModel::DefaultMaxVelocityY);

        const Vec2& knockBackSpeed = Param::Dead::KnockBackSpeed;

        const Vec2 velocity{
            m_body->getForward() * -knockBackSpeed.x,
            -knockBackSpeed.y
        };
        m_body->setVelocity(velocity);

    }

    void DeadState::update(double dt)
    {
        this->onMove(dt);
        if (m_deadTimer.reachedZero()) {
            // ゲームリスタートイベントを開始
            m_pActor->getModule<Events>()->create<Event::GameRestart>();
        }
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
