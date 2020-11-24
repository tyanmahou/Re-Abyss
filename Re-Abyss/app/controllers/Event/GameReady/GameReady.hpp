#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Event/base/IEvent.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>

namespace abyss::ui::Fade
{
    class IrisOut;
}

namespace abyss::Event
{
    class GameReady : public IEvent
    {
        enum class Phase
        {
            Fade,
            End,
        };
    private:
        TimerEx m_timer;
        Ref<ui::Fade::IrisOut> m_fadeUI;
        Phase m_phase = Phase::Fade;

    public:
        GameReady();

        void onStart() override;
        bool update(double dt) override;
        void onEnd() override;
    };
}