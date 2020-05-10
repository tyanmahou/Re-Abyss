#pragma once
#include <abyss/controllers/Actors/Schield/Shot/ShotActor.hpp>

namespace abyss::Schield::Shot
{

    class BaseState : public exp::IState<ShotActor>
    {
    protected:
        BodyModel* m_body;
    public:
        void setup()override;

        void update(double dt) override;

        void lastUpdate(double dt) override;
        void draw() const override;
    };
}