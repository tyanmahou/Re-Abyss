#pragma once
#include <abyss/models/Actors/Commons/StateModel.hpp>
#include <abyss/models/Actors/Commons/ViewModel.hpp>
#include <abyss/models/Actors/Commons/PatternModel.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/components/Actors/Enemy/CodeZero/PartsModel.hpp>

#include <abyss/views/Actors/Enemy/CodeZero/Body/BodyVM.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    class BaseState : public IState
    {
    protected:
        HPModel* m_hp;
        PatternModel* m_pattern;
        PartsModel* m_parts;
        ViewModel<Body::BodyVM>* m_view;
    public:
        BaseState();
        void setup()override;

        void update(double dt) override;

        void draw() const override;
    };
}