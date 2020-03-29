#pragma once
#include <abyss/controllers/Actors/RollingTako/RollingTakoActor.hpp>

namespace abyss
{
    class RollingTakoBaseState : public IState<RollingTakoActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void onCollisionStay(ICollider* col) override;
    };
}
