#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Enemy/CaptainTako/DrawModel.hpp>

namespace abyss::CaptainTako
{
    class BaseState : public IState
    {
    protected:
        BodyModel* m_body;
        DrawModel* m_draw;
    public:
        void setup()override;
    };
}