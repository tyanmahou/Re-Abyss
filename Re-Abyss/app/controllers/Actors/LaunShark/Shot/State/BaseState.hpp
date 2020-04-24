#pragma once
#include <abyss/controllers/Actors/LaunShark/Shot/ShotActor.hpp>

namespace abyss::LaunShark::Shot
{

    class BaseState : public IState<ShotActor>
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