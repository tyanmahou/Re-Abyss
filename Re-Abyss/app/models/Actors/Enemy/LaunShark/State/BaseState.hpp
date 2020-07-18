#pragma once
#include <abyss/controllers/Actors/Enemy/LaunShark/LaunSharkActor.hpp>

namespace abyss::LaunShark
{
    class BaseState : public IOldState<LaunSharkActor>
    {
    protected:
        BodyModel* m_body;
        MapColliderModel* m_mapCol;
        TimeCounterModel* m_timeCounter;

    public:
        void update(double dt) override;
        void setup()override;

        void lastUpdate() override;
    };
}
