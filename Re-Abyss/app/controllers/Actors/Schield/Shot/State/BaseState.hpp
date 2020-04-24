#pragma once
#include <abyss/controllers/Actors/Schield/Shot/ShotActor.hpp>

namespace abyss::Schield::Shot
{

    class BaseState : public IState<ShotActor>
    {
    protected:
        BodyModel* m_body;
    public:
        void setup()override;

        void update(double dt) override;

        void onCollisionStay(ICollider* col) override;

        void draw() const override;
    };
}