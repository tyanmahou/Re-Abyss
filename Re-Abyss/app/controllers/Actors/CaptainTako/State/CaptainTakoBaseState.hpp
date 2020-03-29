#pragma once
#include <abyss/controllers/Actors/CaptainTako/CaptainTakoActor.hpp>

namespace abyss
{
    class CaptainTakoBaseState : public IState<CaptainTakoActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void onCollisionStay(ICollider* col) override;
    };
}