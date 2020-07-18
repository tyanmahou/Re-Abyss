#pragma once
#include <abyss/controllers/Actors/Enemy/Schield/Shot/ShotActor.hpp>

namespace abyss::Schield::Shot
{

    class BaseState : public IOldState<ShotActor>
    {
    protected:
        BodyModel* m_body;
    public:
        void setup()override;

        void update(double dt) override;

        void lastUpdate() override;
        void draw() const override;
    };
}