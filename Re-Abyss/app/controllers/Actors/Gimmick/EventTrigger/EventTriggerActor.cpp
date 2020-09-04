#include "EventTriggerActor.hpp"
#include <abyss/components/Actors/Gimmick/EventTrigger/Main.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    EventTriggerActor::EventTriggerActor(const s3d::FilePath& path)
    {
        this->attach<Main>(this, path);
    }
    bool EventTriggerActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

}
