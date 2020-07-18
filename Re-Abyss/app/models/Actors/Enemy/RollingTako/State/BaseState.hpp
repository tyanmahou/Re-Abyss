#pragma once
#include <abyss/controllers/Actors/Enemy/RollingTako/RollingTakoActor.hpp>

namespace abyss::RollingTako
{
    class BaseState : public IOldState<RollingTakoActor>
    {
    protected:
        BodyModel* m_body;
        MapColliderModel* m_mapCol;
    public:
        void setup()override;

        void update(double dt) override;

        void lastUpdate(double dt) override;

        void draw() const override;
    };
}
