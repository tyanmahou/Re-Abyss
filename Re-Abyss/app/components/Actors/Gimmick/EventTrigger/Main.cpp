#include "Main.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/services/Event/Talk/TalkService.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    Main::Main(IActor* pActor, const s3d::String& path):
        m_pActor(pActor),
        m_path(path)
    {}

    void Main::onStart()
    {
        auto event = Event::Talk::TalkService{}.load(m_path);
        m_pActor->getModule<Events>()->regist(event);
        m_pActor->destroy();
    }

}
