#pragma once
#include <abyss/controllers/Actors/Schield/SchieldActor.hpp>

namespace abyss
{
    class SchieldBaseState : public IState<SchieldActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void update(double dt) override;

        void onCollisionStay(ICollider* col) override;
    };
}
