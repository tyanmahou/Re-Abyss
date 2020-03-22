#pragma once
#include <abyss/controllers/Actors/Player/Shot/PlayerShotActor.hpp>

namespace abyss
{

    class PlayerShotBaseState : public IState<PlayerShotActor>
    {
    protected:
        BodyModel* m_body;
        PlayerShotModel* m_shot;

    public:
        void setup()override;

        void start() override;

        void update(double dt) override;

        void onCollisionStay(ICollider* col) override;

        void draw() const override;
    };
}