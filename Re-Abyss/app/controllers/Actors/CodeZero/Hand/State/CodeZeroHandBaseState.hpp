#pragma once
#include <abyss/controllers/Actors/CodeZero/Hand/CodeZeroHandActor.hpp>

namespace abyss
{
    class CodeZeroHandBaseState : public IState<CodeZeroHandActor>
    {
    protected:
        CodeZeroActor* m_parent;
        BodyModel* m_body;
        RotateModel* m_rotate;
        virtual void updateRight(double dt) =0;
        virtual void updateLeft(double dt) =0;
    public:
        void update(double dt) override;
        void setup()override;
        void draw() const override;
    };
}