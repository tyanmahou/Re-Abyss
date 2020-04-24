#pragma once
#include "BaseState.hpp"
#include <abyss/models/Actors/Commons/PatternModel.hpp>

namespace abyss::CodeZero
{
    class Phase1State : public BaseState
    {
    private:
        PatternModel m_pattern;
    public:
        Phase1State();
        void update(double dt) override;
    };
}