#pragma once
#include <abyss/controllers/Actors/CaptainTako/Shot/ShotActor.hpp>

namespace abyss::CaptainTako::Shot
{

    class BaseState : public exp::IState<ShotActor>
    {
    protected:
        BodyModel* m_body;
    public:
        void setup()override;

        void start() override;

        void update(double dt) override;

        void draw() const override;
    };
}