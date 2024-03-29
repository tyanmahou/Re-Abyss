#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/modules/GameObject/IComponent.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    namespace Hand
    {
        class HandProxy;
    }

    class PartsCtrl : public IComponent
    {
        ActorObj* m_pActor;
        Ref<Hand::HandProxy> m_leftHand;
        Ref<Hand::HandProxy> m_rightHand;
    public:
        PartsCtrl(ActorObj* pActor);

        void onStart() override;

        const Ref<Hand::HandProxy>& getLeftHand()const { return m_leftHand; }
        const Ref<Hand::HandProxy>& getRightHand()const { return m_rightHand; }

        void setActive(bool active) const;
        void setMoveActive(bool active) const;

        bool isShotCharge() const;
    };
}