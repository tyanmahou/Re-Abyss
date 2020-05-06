#include "TriggerManager.hpp"

namespace abyss::Event::Talk
{
    TriggerManager::Factory_t& TriggerManager::operator[](const s3d::String& triggerName)
    {
        return m_events[triggerName];
    }
}
