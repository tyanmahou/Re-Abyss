#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/ScaleCtrl.hpp>
#include <abyss/components/Common/ViewCtrl.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/ParentCtrl.hpp>
#include <abyss/views/Actor/Enemy/CodeZero/Shot/ShotVM.hpp>

namespace abyss::Actor::Enemy::CodeZero::Shot
{
    class BaseState : public IState
    {
    protected:
        ParentCtrl* m_parent;
        Body* m_body;
        ScaleCtrl* m_scale;
        ViewCtrl<ShotVM>* m_view;
    public:
        void setup() override;

        void lastUpdate() override;

        void draw()const override;
    };
}