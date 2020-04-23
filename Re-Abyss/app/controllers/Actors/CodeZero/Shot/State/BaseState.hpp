#pragma once
#include <abyss/controllers/Actors/CodeZero/Shot/ShotActor.hpp>

namespace abyss::CodeZero::Shot
{
    class BaseState : public IState<ShotActor>
    {
    protected:
        BodyModel* m_body;
        ScaleModel* m_scale;
    public:
        void setup() override;

        void draw()const override;
    };
}