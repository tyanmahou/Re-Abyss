#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/BodyModel.hpp>
#include <abyss/models/Actors/Commons/ScaleModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Shot/DrawModel.hpp>

namespace abyss::CodeZero::Shot
{
    class BaseState : public IState
    {
    protected:
        ParentCtrlModel* m_parent;
        BodyModel* m_body;
        ScaleModel* m_scale;
        DrawModel* m_draw;
    public:
        void setup() override;

        void lastUpdate() override;
    };
}