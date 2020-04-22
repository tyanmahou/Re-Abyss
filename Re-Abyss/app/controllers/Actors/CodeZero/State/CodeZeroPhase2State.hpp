#pragma once
#include "CodeZeroBaseState.hpp"
#include <abyss/models/Actors/Commons/PatternModel.hpp>
namespace abyss
{
    class CodeZeroPhase2State : public CodeZeroBaseState
    {
    private:
        PatternModel m_pattern;
    public:
        CodeZeroPhase2State();
        void start() override;
        void update(double dt) override;
    };
}