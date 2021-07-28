#pragma once
#include <abyss/components/Actor/Commons/StateCtrl.hpp>
#include <abyss/components/Common/ViewCtrl.hpp>
#include <abyss/components/Actor/Commons/BehaviorCtrl.hpp>
#include <abyss/components/Actor/Commons/HP.hpp>
#include <abyss/components/Actor/Enemy/CodeZero/PartsCtrl.hpp>

#include <abyss/views/Actor/Enemy/CodeZero/Body/BodyVM.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class BaseState : public IState
    {
    protected:
        HP* m_hp;
        BehaviorCtrl* m_behavior;
        PartsCtrl* m_parts;
        ViewCtrl<Body::BodyVM>* m_view;
    public:
        BaseState();
        void setup()override;

        void update() override;

        void draw() const override;
    };
}