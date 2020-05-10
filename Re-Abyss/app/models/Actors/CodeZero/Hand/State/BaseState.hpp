#pragma once
#include <abyss/controllers/Actors/CodeZero/Hand/HandActor.hpp>

namespace abyss::CodeZero::Hand
{
    class BaseState : public exp::IState<HandActor>
    {
    protected:
        CodeZeroActor* m_parent;
        BodyModel* m_body;
        RotateModel* m_rotate;
        HandModel* m_hand;
    public:
        void update(double dt) override;
        void setup()override;
        void draw() const override;
    };
}