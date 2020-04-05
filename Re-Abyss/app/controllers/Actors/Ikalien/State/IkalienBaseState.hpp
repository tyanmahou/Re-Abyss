#pragma once
#include <abyss/controllers/Actors/Ikalien/IkalienActor.hpp>

namespace abyss
{
    class IkalienBaseState : public IState<IkalienActor>
    {
    protected:
        BodyModel* m_body;
        RotateModel* m_rotate;
    public:
        void setup()override;

        void onCollisionStay(ICollider* col) override;
    };
}
