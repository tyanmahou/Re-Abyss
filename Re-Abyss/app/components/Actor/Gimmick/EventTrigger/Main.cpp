#include <abyss/components/Actor/Gimmick/EventTrigger/Main.hpp>
#include <abyss/modules/Novel/Novels.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Novel/TalkBuilder.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    Main::Main(ActorObj* pActor, const s3d::String& path):
        m_pActor(pActor),
        m_path(path)
    {}

    void Main::onStart()
    {
        m_pActor->getModule<Novels>()->create<Novel::TalkBuilder>(m_path);

        m_pActor->destroy();
    }

}
