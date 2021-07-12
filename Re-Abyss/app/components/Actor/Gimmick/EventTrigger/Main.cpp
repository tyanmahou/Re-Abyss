#include "Main.hpp"
#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Event/Talk/Builder.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    Main::Main(ActorObj* pActor, const s3d::String& path):
        m_pActor(pActor),
        m_path(path)
    {}

    void Main::onStart()
    {
        m_pActor->getModule<Events>()->create<Event::Talk::Builder>(m_path);

        m_pActor->destroy();
    }

}
