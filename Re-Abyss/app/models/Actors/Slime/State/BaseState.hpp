#pragma once
#include <abyss/controllers/Actors/Slime/SlimeActor.hpp>

namespace abyss::Slime
{

    class BaseState : public exp::IState<SlimeActor>
    {
    protected:
        BodyModel* m_body;
        // 
        virtual void onColisionMapUp(){}
    public:
        void setup()override;

        void update(double dt) override;

        void draw() const override;

        void onCollisionStay(IActor* col) override;
        void lastUpdate(double dt);
    };
}