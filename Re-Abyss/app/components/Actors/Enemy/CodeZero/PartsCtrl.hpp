#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/components/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    namespace Head
    {
        class HeadActor;
    }
    namespace Hand
    {
        class HandActor;
    }

    class PartsCtrl : public IComponent
    {
        IActor* m_pActor;
        Ref<IActor> m_head;
        Ref<Hand::HandActor> m_leftHand;
        Ref<Hand::HandActor> m_rightHand;
    public:
        PartsCtrl(IActor* pActor);

        void onStart() override;

        const Ref<IActor>& getHead()const { return m_head; }
        const Ref<Hand::HandActor>& getLeftHand()const { return m_leftHand; }
        const Ref<Hand::HandActor>& getRightHand()const { return m_rightHand; }

        void setActive(bool active) const;
    };
}