#pragma once
#include <Siv3D/HashTable.hpp>
#include <Siv3D/String.hpp>
#include <abyss/modules/Event/Talk/TalkObj.hpp>

namespace abyss::Event::Talk
{
    class TriggerFactory
    {
        using Factory_t = std::function<void(TalkObj*)>;
        s3d::HashTable<s3d::String, Factory_t> m_factories;

    public:

        Factory_t& operator[](const s3d::String& triggerName);
    };
}