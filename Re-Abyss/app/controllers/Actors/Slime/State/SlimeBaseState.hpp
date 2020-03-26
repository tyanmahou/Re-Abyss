#pragma once
#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>

namespace abyss
{

    class SlimeBaseState : public IState<SlimeActor>
    {
    protected:
        BodyModel* m_body;
        // 
        virtual void onColisionMapUp(){}
    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void onCollisionEnter(ICollider* col) override;
        void onCollisionStay(ICollider* col) override;
    };
}