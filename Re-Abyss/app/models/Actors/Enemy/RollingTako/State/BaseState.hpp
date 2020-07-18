#pragma once
#include <abyss/controllers/Actors/Enemy/RollingTako/RollingTakoActor.hpp>
#include <abyss/models/Actors/base/StateModel.hpp>
#include <abyss/models/Actors/Enemy/RollingTako/DrawModel.hpp>

namespace abyss::RollingTako
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        MapColliderModel* m_mapCol;
        DrawModel* m_draw;
    public:
        void setup()override;

        void update(double dt) override;

        void lastUpdate() override;
    };
}
