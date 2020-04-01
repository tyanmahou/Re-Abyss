#pragma once
#include <abyss/controllers/Actors/LaunShark/LaunSharkActor.hpp>

namespace abyss
{
    class LaunSharkBaseState : public IState<LaunSharkActor>
    {
    protected:
        BodyModel* m_body;

    public:
        void setup()override;

        void onCollisionStay(ICollider* col) override;
    };
}
