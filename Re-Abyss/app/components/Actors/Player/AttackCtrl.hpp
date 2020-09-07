#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss::Actor::Player
{
    class AttackCtrlModel : 
        public IComponent
    {
        TimerEx m_timer;
        IActor* m_pActor = nullptr;
    public:
        AttackCtrlModel(IActor* pActor);

        void reset();
        void startAttack();
        bool isAttacking() const;
    };
}