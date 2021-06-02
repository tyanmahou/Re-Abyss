#include "DeadState.hpp"
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Commons/FallChecker.hpp>
#include <abyss/components/Actor/Commons/DamageCtrl.hpp>
#include <abyss/params/Actor/Player/Param.hpp>
#include <abyss/views/Actor/Player/PlayerVM.hpp>

#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/components/Actor/utils/ActorUtils.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Player
{
    Task<> DeadState::start()
    {
        co_yield BaseState::start();

        // 無敵時間をなしに
        m_pActor->find<HP>()->setInvincibleTime(0);

        // サウンド停止
        m_pActor->getModule<Sound>()->stop(0.5s);

        // 地震
        m_pActor->getModule<Camera>()->startQuake(5.0, 0.5);

        m_pActor->find<AudioSource>()->play(U"Dead");

        m_pActor->find<StateChecker>()->setIsDeadState(true);
        m_body
            ->setAccelX(0)
            .setMaxVelocityY(Body::DefaultMaxVelocityY);

        if (!m_pActor->find<FallChecker>()->isFall()) {
            const Vec2& knockBackSpeed = Param::Dead::KnockBackSpeed;

            auto nextForward = m_body->getForward();
            if (const auto& damage = m_pActor->find<DamageCtrl>()->getData()) {
                auto toPlayer = m_body->getCenterPos() - damage->pos;
                if (toPlayer.x > 0) {
                    nextForward = Forward::Left;
                } else if (toPlayer.x < 0) {
                    nextForward = Forward::Right;
                }
            }
            const Vec2 velocity{
                nextForward * -knockBackSpeed.x,
                -knockBackSpeed.y
            };
            m_body
                ->setVelocity(velocity)
                .setForward(nextForward);
        }

        // ダメージ受けない
        m_pActor->find<DamageCtrl>()->setActive(false);

        // アニメ用タイマー開始
        m_deadTimer = ActorUtils::CreateTimer(*m_pActor, Param::Dead::AnimeTimeSec, true);

        // 待ち
        co_yield BehaviorUtils::WaitForSeconds(m_pActor, Param::Dead::TimeSec);
        co_return;
    }

    void DeadState::update()
    {
    }

    void DeadState::onDraw(const PlayerVM& view) const
    {
        view.drawStateDead(s3d::Saturate(m_deadTimer.progress0_1()));
    }

    DeadState::DeadState()
    {}

}
