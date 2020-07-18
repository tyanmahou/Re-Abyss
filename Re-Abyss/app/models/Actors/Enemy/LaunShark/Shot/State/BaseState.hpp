#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Enemy/LaunShark/Shot/DrawModel.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::LaunShark::Shot
{

    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        RotateModel* m_rotate;
        DrawModel* m_draw;
    public:
        void setup()override;
    };
}