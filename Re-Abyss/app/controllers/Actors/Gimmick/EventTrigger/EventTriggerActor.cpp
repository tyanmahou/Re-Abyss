#include "EventTriggerActor.hpp"
#include <abyss/models/Actors/Gimmick/EventTrigger/MainModel.hpp>

namespace abyss::EventTrigger
{
    EventTriggerActor::EventTriggerActor(const s3d::FilePath& path)
    {
        this->attach<MainModel>(this, path);
    }
    bool EventTriggerActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

}
