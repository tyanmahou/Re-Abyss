#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/Head/HeadCtrl.hpp>
#include <abyss/views/Actors/Enemy/CodeZero/Head/HeadVM.hpp>

namespace abyss::Actor::Enemy::CodeZero::Head
{
    class BaseState : public IState
    {
    protected:
        ParentCtrl* m_parent;
        HeadCtrl* m_head;

        ViewCtrl<HeadVM>* m_view;
    public:
        void setup()override;

        void update() override;

        void draw()const override;
    };
}