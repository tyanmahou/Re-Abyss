#include "TriggerManager.hpp"

namespace abyss::Event::Talk
{
    std::shared_ptr<IEvent>& TriggerManager::operator[](const s3d::String& triggerName)
    {
        return m_events[triggerName];
    }
}
