#pragma once
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandProxy : 
        public IComponent
    {
    public:
        HandProxy(ActorObj* pActor);
        void onStart()override;

        bool tryAttack();
        bool tryPursuit();
        bool tryShotCharge();

        bool isShotCharge()const;
        bool isPursuit() const;

        ActorObj* getActor() const
        {
            return m_pActor;
        }
    private:
        ActorObj* m_pActor;
        Ref<StateCtrl> m_state;
    };
}