#pragma once
#include <memory>
#include <abyss/modules/Event/Talk/TalkEvent.hpp>

namespace abyss::Event::Talk
{
    class TalkService
    {
    public:
        std::shared_ptr<TalkEvent> load(const s3d::String& path);
    };
}