#pragma once
#include "BaseState.hpp"
#include <abyss/models/Actors/Commons/PatternModel.hpp>
namespace abyss::CodeZero
{
    class Phase2State : public BaseState
    {
    private:
        PatternModel m_pattern;
    public:
        Phase2State();
        void start() override;
        void update(double dt) override;
    };
}