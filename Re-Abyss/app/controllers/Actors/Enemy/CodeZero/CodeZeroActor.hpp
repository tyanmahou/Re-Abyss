#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss
{
    struct CodeZeroEntity;
}
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
    
    namespace Body
    {
        class BodyVM;
    }

    class CodeZeroActor :
        public EnemyActor
    {
    private:
        Ref<StateModel> m_state;

        Ref<Head::HeadActor> m_head;
        Ref<Hand::HandActor> m_leftHand;
        Ref<Hand::HandActor> m_rightHand;

    public:
        CodeZeroActor(const CodeZeroEntity& entity);

        void start()override;

        bool accept(const ActVisitor& visitor) override;

        Hand::HandActor* getLeftHand()const { return m_leftHand.get(); }
        Hand::HandActor* getRightHand()const { return m_rightHand.get(); }

        bool isPhase1()const;
        bool isPhase2()const;
        bool isPhase3()const;
        bool isShotCharge()const;

        void setActiveAll(bool active);
    };
}