#pragma once
#include "CodeZeroBaseState.hpp"
#include <abyss/models/Actors/Commons/PatternModel.hpp>
namespace abyss
{
    class CodeZeroPhase3State : public CodeZeroBaseState
    {
    private:
        PatternModel m_pattern;
    public:
        CodeZeroPhase3State();
        void start() override;
        void update(double dt) override;
    };
}