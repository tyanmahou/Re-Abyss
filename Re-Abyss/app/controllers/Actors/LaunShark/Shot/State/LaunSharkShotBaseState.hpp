#pragma once
#include <abyss/controllers/Actors/LaunShark/Shot/LaunSharkShotActor.hpp>

namespace abyss
{

    class LaunSharkShotBaseState : public IState<LaunSharkShotActor>
    {
    protected:
        BodyModel* m_body;
        HPModel* m_hp;
        RotateModel* m_rotate;

        void destroy();
    public:
        void setup()override;
        void onCollisionStay(ICollider* col) override;
    };
}