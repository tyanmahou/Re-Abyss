#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Event/base/IEvent.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::ui::Fade
{
    class SmoothCircle;
}

namespace abyss::Event
{
    class GameRestart : public IEvent
    {
        enum class Phase
        {
            Fade,
            End,
        };
    private:
        TimerEx m_timer;
        Ref<ui::Fade::SmoothCircle> m_fadeUI;
        Phase m_phase = Phase::Fade;

    public:
        GameRestart();

        void onStart() override;
        bool update(double dt) override;
        void onEnd() override;
    };
}