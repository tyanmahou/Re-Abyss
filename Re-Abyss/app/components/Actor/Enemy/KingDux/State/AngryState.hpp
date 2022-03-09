#pragma once
#include <abyss/components/Actor/Enemy/KingDux/State/BaseState.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/models/Camera/QuakeModel.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    class AngryState final :
        public BaseState
    {
        enum class Phase
        {
            Open,
            Wait,
            Close,
        };
    public:
        void start() override;
        void end() override;
        Coro::Task<> task() override;
        void update() override;
    private:
        Ref<QuakeModel> m_quake;
        Phase m_phase = Phase::Open;
        TimeLite::Timer m_animTimer{};
    };
}