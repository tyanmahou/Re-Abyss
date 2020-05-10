#pragma once
#include <abyss/controllers/Actors/CaptainTako/CaptainTakoActor.hpp>

namespace abyss::CaptainTako
{
    class BaseState : public exp::IState<CaptainTakoActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void onCollisionStay(IActor* col) override;
    };
}