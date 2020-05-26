#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
namespace abyss::Player
{
    class AttackCtrlModel : 
        public IComponent
    {
        TimerEx m_timer;
        IActor* m_pActor = nullptr;
    public:
        AttackCtrlModel(IActor* pActor);

        void startAttack();
        bool isAttacking() const;
    };
}