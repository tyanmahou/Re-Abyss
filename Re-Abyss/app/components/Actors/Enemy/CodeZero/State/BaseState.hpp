#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/components/Actors/Commons/ViewCtrl.hpp>
#include <abyss/components/Actors/Commons/PatternCtrl.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/PartsCtrl.hpp>

#include <abyss/views/Actors/Enemy/CodeZero/Body/BodyVM.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class BaseState : public IState
    {
    protected:
        HPModel* m_hp;
        PatternCtrl* m_pattern;
        PartsCtrl* m_parts;
        ViewCtrl<Body::BodyVM>* m_view;
    public:
        BaseState();
        void setup()override;

        void update(double dt) override;

        void draw() const override;
    };
}