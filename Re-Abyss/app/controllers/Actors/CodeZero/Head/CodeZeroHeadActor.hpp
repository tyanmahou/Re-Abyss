#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>

namespace abyss
{
    class CodeZeroActor;
    class CodeZeroHeadVM;

    class CodeZeroHeadActor:
        public IActor,
        public Receiver
    {
    public:
        enum State
        {
            Base,
        };
    private:
        CodeZeroActor* m_parent;
        HPModel* m_parentHp;
        Forward m_forward;

        StateManager<CodeZeroHeadActor> m_state;
        std::shared_ptr<CodeZeroHeadVM> m_view;
    public:
        CodeZeroHeadActor(CodeZeroActor* parent, HPModel* m_parentHp);

        s3d::Vec2 getPos()const;

        void update(double dt)override;
        void draw()const;

        CShape getCollider() const override;
        void onCollisionStay(ICollider* col) override;
        bool accept(const ActVisitor& visitor) override;

        CodeZeroHeadVM* getBindedView()const;
    };
}