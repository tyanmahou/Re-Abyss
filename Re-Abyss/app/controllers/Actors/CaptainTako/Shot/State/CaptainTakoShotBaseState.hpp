#pragma once
#include <abyss/controllers/Actors/CaptainTako/Shot/CaptainTakoShotActor.hpp>

namespace abyss
{

    class CaptainTakoShotBaseState : public IState<CaptainTakoShotActor>
    {
    protected:
        BodyModel* m_body;
    public:
        void setup()override;

        void start() override;

        void update(double dt) override;

        void onCollisionStay(ICollider* col) override;

        void draw() const override;
    };
}