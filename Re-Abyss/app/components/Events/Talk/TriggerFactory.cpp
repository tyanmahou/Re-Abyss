#include "TriggerFactory.hpp"

namespace abyss::Event::Talk
{
    TriggerFactory::Factory_t& TriggerFactory::operator[](const s3d::String& triggerName)
    {
        return m_factories[triggerName];
    }
}
