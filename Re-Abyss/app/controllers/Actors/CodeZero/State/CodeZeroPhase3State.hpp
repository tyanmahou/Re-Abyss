#pragma once
#include "CodeZeroBaseState.hpp"

namespace abyss
{
    class CodeZeroPhase3State : public CodeZeroBaseState
    {
    private:
        TimerEx m_timer;
        s3d::int32 m_step = 0;
    public:
        CodeZeroPhase3State();
        void start() override;
        void update(double dt) override;
    };
}