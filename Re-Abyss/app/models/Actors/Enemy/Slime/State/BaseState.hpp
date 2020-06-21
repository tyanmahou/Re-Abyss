#pragma once
#include <abyss/controllers/Actors/Enemy/Slime/SlimeActor.hpp>
#include <abyss/models/Actors/Commons/MapColliderModel.hpp>

namespace abyss::Slime
{

    class BaseState : public IState<SlimeActor>
    {
    protected:
        BodyModel* m_body;
        MapColliderModel* m_mapCol;
    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void lastUpdate(double dt);
    };
}