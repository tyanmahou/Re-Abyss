#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

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
        StateManager<CodeZeroActor> m_state;
        std::shared_ptr<Body::BodyVM> m_view;

        std::shared_ptr<Head::HeadActor> m_head;
        std::shared_ptr<Hand::HandActor> m_leftHand;
        std::shared_ptr<Hand::HandActor> m_rightHand;

    public:
        CodeZeroActor(const CodeZeroEntity& entity);

        void start()override;
        void update(double dt)override;
        void draw()const;

        CShape getCollider() const override;

        bool accept(const ActVisitor& visitor) override;

        Body::BodyVM* getBindedView()const;

        void onDead();

        Hand::HandActor* getLeftHand()const { return m_leftHand.get(); }
        Hand::HandActor* getRightHand()const { return m_rightHand.get(); }

        bool isPhase1()const { return m_state.getState() == State::Phase1; }
        bool isPhase2()const { return m_state.getState() == State::Phase2; }
        bool isPhase3()const { return m_state.getState() == State::Phase3; }
        bool isShotCharge()const;
    };
}