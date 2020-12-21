#pragma once
#include <Siv3D/HashTable.hpp>
#include <Siv3D/String.hpp>
#include <abyss/modules/Event/base/IEvent.hpp>

namespace abyss::Event::Talk
{
    class TriggerManager
    {
        using Factory_t = std::function<std::unique_ptr<IEvent>()>;
        s3d::HashTable<s3d::String, Factory_t> m_events;

    public:

        Factory_t& operator[](const s3d::String& triggerName);
    };
}