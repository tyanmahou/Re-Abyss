#pragma once
#include <abyss/controllers/Actors/RollingTako/RollingTakoActor.hpp>

namespace abyss::RollingTako
{
    class BaseState : public IState<RollingTakoActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void update(double dt) override;

        void lastUpdate(double dt) override;

        void draw() const override;

        void onCollisionMap(ColDirection colDir);

        void onCollisionStay(ICollider* col) override;
    };
}
