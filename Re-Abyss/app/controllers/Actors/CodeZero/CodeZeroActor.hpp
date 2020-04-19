#pragma once
#include <abyss/controllers/Actors/Enemy/EnemyActor.hpp>
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>

namespace abyss
{
    struct CodeZeroEntity;
    class CodeZeroHeadActor;
    class CodeZeroHandActor;
    class CodeZeroBodyVM;

    class CodeZeroActor :
        public EnemyActor
    {
    public:
        enum State
        {
            Base,
        };
    private:
        StateManager<CodeZeroActor> m_state;
        std::shared_ptr<CodeZeroBodyVM> m_view;

        std::shared_ptr<CodeZeroHeadActor> m_head;
        std::shared_ptr<CodeZeroHandActor> m_leftHand;
        std::shared_ptr<CodeZeroHandActor> m_rightHand;

    public:
        CodeZeroActor(const CodeZeroEntity& entity);

        void start()override;
        void update(double dt)override;
        void draw()const;

        CShape getCollider() const override;

        bool accept(const ActVisitor& visitor) override;

        CodeZeroBodyVM* getBindedView()const;

        void onDead() override;

        CodeZeroHandActor* getLeftHand()const { return m_leftHand.get(); }
        CodeZeroHandActor* getRightHand()const { return m_rightHand.get(); }
    };
}