#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/ParentCtrlModel.hpp>
#include <abyss/models/Actors/Enemy/CodeZero/Head/HeadModel.hpp>

namespace abyss::CodeZero::Head
{
    class BaseState : public IState
    {
    protected:
        HPModel* m_hp;
        CodeZeroActor* m_parent;
        HeadModel* m_head;
    public:
        void setup()override;

        void update(double dt) override;
    };
}