#pragma once
#include <memory>
#include <Siv3D/String.hpp>
#include <abyss/modules/Event/base/IEvent.hpp>

namespace abyss::Event::Talk
{
    class TriggerManager;

    class TriggerEvent : public IEvent
    {
        s3d::String m_triggerName;
        std::unique_ptr<IEvent> m_event;

        std::shared_ptr<TriggerManager> m_triggerManager;
    public:
        TriggerEvent& setName(const s3d::String& name)
        {
            m_triggerName = name;
            return *this;
        }
        TriggerEvent& setTriggerManager(const std::shared_ptr<TriggerManager>& triggerManager)
        {
            m_triggerManager = triggerManager;
            return *this;
        }

        void onStart() override;
        bool update(double dt) override;
        void onEnd() override;
    };
}