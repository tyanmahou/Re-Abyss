#pragma once
#include <abyss/controllers/Actors/CodeZero/CodeZeroActor.hpp>
#include <abyss/models/Actors/Commons/PatternModel.hpp>

namespace abyss::CodeZero
{
    class BaseState : public exp::IState<CodeZeroActor>
    {
    protected:
        HPModel* m_hp;
        PatternModel* m_pattern;
    public:
        BaseState();
        void setup()override;

        void update(double dt) override;

        void draw() const override;
    };
}