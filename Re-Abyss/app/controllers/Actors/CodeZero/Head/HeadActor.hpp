#pragma once
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/controllers/Actors/base/Receiver.hpp>
#include <abyss/types/Forward.hpp>
#include <abyss/controllers/Actors/base/IState.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>

namespace abyss::CodeZero
{
    class CodeZeroActor;
}
namespace abyss::CodeZero::Head
{
    class HeadVM;

    class HeadActor:
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

        StateManager<HeadActor> m_state;
        std::shared_ptr<HeadVM> m_view;
    public:
        HeadActor(CodeZeroActor* parent, HPModel* m_parentHp);

        s3d::Vec2 getPos()const;

        void update(double dt)override;
        void draw()const;

        CShape getCollider() const override;
        void onCollisionStay(ICollider* col) override;
        bool accept(const ActVisitor& visitor) override;

        HeadVM* getBindedView()const;
    };
}