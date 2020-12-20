#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandProxy : 
        public IComponent
    {
    public:
        HandProxy(IActor* pActor);
        void onStart()override;

        bool tryAttack();
        bool tryPursuit();
        bool tryShotCharge();

        bool isShotCharge()const;
        bool isPursuit() const;

        IActor* getActor() const
        {
            return m_pActor;
        }
    private:
        IActor* m_pActor;
        Ref<StateCtrl> m_state;
    };
}