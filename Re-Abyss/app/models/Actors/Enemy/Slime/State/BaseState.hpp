#pragma once
#include <abyss/controllers/Actors/Enemy/Slime/SlimeActor.hpp>
#include <abyss/models/Actors/Commons/MapColResultModel.hpp>

namespace abyss::Slime
{

    class BaseState : public IState<SlimeActor>
    {
    protected:
        BodyModel* m_body;
        MapColResultModel* m_mapColResult;
    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void lastUpdate(double dt);
    };
}