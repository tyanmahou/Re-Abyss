#include <abyss/components/Actor/Enemy/CodeZero/State/AngryState.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>
#include <abyss/components/Actor/Common/ColorAnim/InvincibleColor.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    void AngryState::start()
    {
        // 無敵
        m_damageCtrl->setInvincibleState(true);
        m_pActor->find<ColorAnim::InvincibleColor>()->startAnim(2.0);

        // 頭固定
        m_head->setActive(false);

        // 画面フラッシュ
        m_pActor->getModule<SpecialEffects>()->flush()->start(0, 0.5);

        // 地震
        m_pActor->getModule<Camera>()->startQuake(10.0, 0.3);

        m_parts->getLeftHand()->tryAngry();
        m_parts->getRightHand()->tryAngry();
    }
    void AngryState::end()
    {
        m_pActor->find<ColorAnim::InvincibleColor>()->endAnim();
    }

    Coro::Fiber<> AngryState::task()
    {
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 2.0);

        m_parts->getLeftHand()->tryPursuit(true);
        m_parts->getRightHand()->tryPursuit(true);
        this->changeState<WaitState>();
    }

    void AngryState::update()
    {
    }
}
