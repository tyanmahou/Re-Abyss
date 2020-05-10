#pragma once
#include <abyss/controllers/Actors/CodeZero/Shot/ShotActor.hpp>

namespace abyss::CodeZero::Shot
{
    class BaseState : public exp::IState<ShotActor>
    {
    protected:
        ParentCtrlModel* m_parent;
        BodyModel* m_body;
        ScaleModel* m_scale;
    public:
        void setup() override;

        void lastUpdate(double dt) override;
        void draw()const override;
    };
}