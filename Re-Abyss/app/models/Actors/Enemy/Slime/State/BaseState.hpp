#pragma once
#include <abyss/controllers/Actors/Enemy/Slime/SlimeActor.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>
#include <abyss/models/Actors/Enemy/Slime/DrawModel.hpp>

namespace abyss::Slime
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
        void lastUpdate(double dt);
    };
}