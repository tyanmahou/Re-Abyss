#pragma once
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/Hand/HandDesc.hpp>

namespace abyss::Actor::Enemy::CodeZero::Hand
{
    class HandProxy : 
        public IComponent
    {
    public:
        HandProxy(ActorObj* pActor);
        void onStart()override;

        bool tryAngry();
        bool tryAngryEnd();
        bool tryAttack();
        bool tryPursuit(bool slowStart = false);
        bool tryPursuit(const HandDesc& desc, bool slowStart = false);
        bool tryShotCharge();
        bool tryRollingAttack(bool isReverse);
        void dead();

        bool isShotCharge()const;
        bool isPursuit() const;

        void setMoveActive(bool isActive);

        ActorObj* getActor() const
        {
            return m_pActor;
        }
        void destroy();
    private:
        ActorObj* m_pActor;
        Ref<StateCtrl> m_state;
    };
}
