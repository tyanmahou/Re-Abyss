#include "Main.hpp"
#include <abyss/modules/System/System.hpp>
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Events/Talk/Builder.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    Main::Main(IActor* pActor, const s3d::String& path):
        m_pActor(pActor),
        m_path(path)
    {}

    void Main::onStart()
    {
        m_pActor->getModule<Events>()->create<Event::Talk::Builder>(m_path);

        m_pActor->destroy();
    }

}
