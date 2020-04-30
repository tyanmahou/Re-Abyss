#pragma once
#include <Siv3D/HashTable.hpp>
#include <Siv3D/String.hpp>
#include <abyss/controllers/Event/base/IEvent.hpp>

namespace abyss::Event::Talk
{
    class TriggerManager
    {
        s3d::HashTable<s3d::String, std::shared_ptr<IEvent>> m_events;

    public:

        std::shared_ptr<IEvent>& operator[](const s3d::String& triggerName);
    };
}