#pragma once
#include <abyss/commons/Fwd.hpp>
#include <abyss/controllers/Event/base/IEvent.hpp>
#include <abyss/utils/Ref/Ref.hpp>
#include <abyss/utils/TimerEx/TimerEx.hpp>
#include <abyss/models/GlobalTime/GlobalTimeScaleModel.hpp>

namespace abyss::ui::Fade
{
    class IrisOut;
}

namespace abyss::Event
{
    class GameRestart : public IEvent
    {
        enum class Phase
        {
            Wait,
            Fade,
            End,
        };
    private:
        TimerEx m_waitTimer;
        TimerEx m_fadeTimer;
        Ref<ui::Fade::IrisOut> m_fadeUI;
        std::shared_ptr<GlobalTimeScaleModel> m_globalTimeScale;
        Phase m_phase = Phase::Wait;

    public:
        GameRestart();

        void onStart() override;
        bool update(double dt) override;
        void onEnd() override;
    };
}