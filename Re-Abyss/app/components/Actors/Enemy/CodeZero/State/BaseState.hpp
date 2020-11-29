#pragma once
#include <abyss/components/Actors/Commons/StateCtrl.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Commons/BehaviorCtrl.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/PartsCtrl.hpp>

#include <abyss/views/Actors/Enemy/CodeZero/Body/BodyVM.hpp>

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

        void update(double dt) override;

        void draw() const override;
    };
}