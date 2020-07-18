#pragma once
#include <abyss/models/Actors/base/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/RotateModel.hpp>
#include <abyss/models/Actors/Enemy/Ikalien/DrawModel.hpp>

namespace abyss::Ikalien
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
