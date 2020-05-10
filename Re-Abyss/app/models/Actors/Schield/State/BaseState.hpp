#pragma once
#include <abyss/controllers/Actors/Schield/SchieldActor.hpp>

namespace abyss::Schield
{
    class BaseState : public exp::IState<SchieldActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void update(double dt) override;

        void onCollisionStay(IActor* col) override;
    };
}
