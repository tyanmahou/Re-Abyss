#pragma once
#include "BaseState.hpp"
#include <abyss/models/Actors/Commons/PatternModel.hpp>
namespace abyss::CodeZero
{
    class Phase3State : public BaseState
    {
    private:
        PatternModel m_pattern;
    public:
        Phase3State();
        void start() override;
        void update(double dt) override;
    };
}