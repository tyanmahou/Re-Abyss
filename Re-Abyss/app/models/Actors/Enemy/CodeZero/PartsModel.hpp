#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::CodeZero
{
    namespace Head
    {
        class HeadActor;
    }
    namespace Hand
    {
        class HandActor;
    }

    class PartsModel : public IComponent
    {
        IActor* m_pActor;
        Ref<Head::HeadActor> m_head;
        Ref<Hand::HandActor> m_leftHand;
        Ref<Hand::HandActor> m_rightHand;
    public:
        PartsModel(IActor* pActor);

        void setup() override;
        void onStart() override;

        const Ref<Head::HeadActor>& getHead()const { return m_head; }
        const Ref<Hand::HandActor>& getLeftHand()const { return m_leftHand; }
        const Ref<Hand::HandActor>& getRightHand()const { return m_rightHand; }

        void setActive(bool active) const;
    };
}