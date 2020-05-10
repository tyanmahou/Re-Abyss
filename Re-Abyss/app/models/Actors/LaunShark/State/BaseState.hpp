#pragma once
#include <abyss/controllers/Actors/LaunShark/LaunSharkActor.hpp>

namespace abyss::LaunShark
{
    class BaseState : public exp::IState<LaunSharkActor>
    {
    protected:
        BodyModel* m_body;
        TimeCounterModel* m_timeCounter;

        void tryReverse(ColDirection col);

        virtual void onCollisionMap(ColDirection col);
    public:
        void update(double dt) override;
        void setup()override;

        void lastUpdate(double dt) override;
        void onCollisionStay(IActor* col) override;
    };
}
