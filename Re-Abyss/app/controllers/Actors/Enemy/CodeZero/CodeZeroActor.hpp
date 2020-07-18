#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/models/Actors/base/OldStateModel.hpp>

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
    public:
        enum State
        {
            Base,
            Phase1,
            Phase2,
            Phase3,
        };
    private:
        Ref<OldStateModel<CodeZeroActor>> m_state;
        std::shared_ptr<Body::BodyVM> m_view;

        Ref<Head::HeadActor> m_head;
        Ref<Hand::HandActor> m_leftHand;
        Ref<Hand::HandActor> m_rightHand;

    public:
        CodeZeroActor(const CodeZeroEntity& entity);

        void start()override;

        bool accept(const ActVisitor& visitor) override;

        Body::BodyVM* getBindedView()const;

        Hand::HandActor* getLeftHand()const { return m_leftHand.get(); }
        Hand::HandActor* getRightHand()const { return m_rightHand.get(); }

        bool isPhase1()const { return m_state->getState() == State::Phase1; }
        bool isPhase2()const { return m_state->getState() == State::Phase2; }
        bool isPhase3()const { return m_state->getState() == State::Phase3; }
        bool isShotCharge()const;

        void setActiveAll(bool active);
    };
}