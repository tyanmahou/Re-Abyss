#pragma once
#include <queue>
#include <memory>
#include <abyss/modules/Event/base/IEvent.hpp>

namespace abyss::Event::Talk
{
    class TalkEvent : public IEvent
    {
    private:
        std::queue<std::shared_ptr<IEvent>> m_events;
        bool m_doneCurrentInit = false;
    public:

        TalkEvent& addEvent(const std::shared_ptr<IEvent>& event);

        void onStart() override;
        bool update(double dt) override;

        void onEnd() override;
    };
}