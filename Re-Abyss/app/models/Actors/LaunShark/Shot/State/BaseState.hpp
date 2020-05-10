#pragma once
#include <abyss/controllers/Actors/LaunShark/Shot/ShotActor.hpp>

namespace abyss::LaunShark::Shot
{

    class BaseState : public exp::IState<ShotActor>
    {
    protected:
        BodyModel* m_body;
        RotateModel* m_rotate;

    public:
        void setup()override;
    };
}