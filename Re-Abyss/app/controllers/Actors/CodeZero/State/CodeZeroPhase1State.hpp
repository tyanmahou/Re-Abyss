#pragma once
#include "CodeZeroBaseState.hpp"
#include <abyss/models/Actors/Commons/PatternModel.hpp>

namespace abyss
{
    class CodeZeroPhase1State : public CodeZeroBaseState
    {
    private:
        PatternModel m_pattern;
    public:
        CodeZeroPhase1State();
        void update(double dt) override;
    };
}