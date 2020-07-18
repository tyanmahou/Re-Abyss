#pragma once
#include <abyss/models/Actors/base/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/AudioSourceModel.hpp>
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
        void lastUpdate();
    };
}