#pragma once
#include <abyss/controllers/Actors/Schield/Shot/SchieldShotActor.hpp>

namespace abyss
{

    class SchieldShotBaseState : public IState<SchieldShotActor>
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