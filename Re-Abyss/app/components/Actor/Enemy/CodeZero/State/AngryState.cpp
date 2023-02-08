#include <abyss/components/Actor/Enemy/CodeZero/State/AngryState.hpp>

#include <abyss/components/Actor/Enemy/CodeZero/State/WaitState.hpp>
#include <abyss/components/Actor/Common/ColorAnim/InvincibleColor.hpp>
#include <abyss/modules/Sfx/SpecialEffects.hpp>
#include <abyss/components/Actor/utils/BehaviorUtil.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    void AngryState::start()
    {
        m_damageCtrl->setInvincibleState(true);
        m_pActor->find<ColorAnim::InvincibleColor>()->startAnim(2.0);

        // 画面フラッシュ
        m_pActor->getModule<SpecialEffects>()->flush()->start(0, 0.5);
    }
    void AngryState::end()
    {
        m_pActor->find<ColorAnim::InvincibleColor>()->endAnim();
    }

    Coro::Fiber<> AngryState::task()
    {
        co_await BehaviorUtil::WaitForSeconds(m_pActor, 2.0);
        this->changeState<WaitState>();
    }

    void AngryState::update()
    {
    }
}
