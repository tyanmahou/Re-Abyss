#include "EventTriggerActor.hpp"
#include <abyss/controllers/ActionSystem/ActionSystem.hpp>
#include <abyss/services/Event/Talk/TalkService.hpp>

namespace abyss::EventTrigger
{
    EventTriggerActor::EventTriggerActor(const s3d::FilePath& path):
        m_path(path)
    {

    }
    void EventTriggerActor::start()
    {
        auto event = Event::Talk::TalkService{}.load(m_path);
        this->getModule<Events>()->regist(event);
        this->destroy();
    }
    bool EventTriggerActor::accept(const ActVisitor& visitor)
    {
        return visitor.visit(*this);
    }

}
