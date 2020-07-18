#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Enemy/Schield/FaceCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/Schield/DrawModel.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::Schield
{
    class BaseState : public IState
    {
    protected:
        FaceCtrlModel* m_face;
        BodyModel* m_body;
        DrawModel* m_draw;
    public:
        void setup()override;
    };
}
