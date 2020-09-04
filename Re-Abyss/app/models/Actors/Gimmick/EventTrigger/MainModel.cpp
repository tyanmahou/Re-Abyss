#include "MainModel.hpp"
#include <abyss/controllers/System/System.hpp>
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/services/Event/Talk/TalkService.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    MainModel::MainModel(IActor* pActor, const s3d::String& path):
        m_pActor(pActor),
        m_path(path)
    {}

    void MainModel::onStart()
    {
        auto event = Event::Talk::TalkService{}.load(m_path);
        m_pActor->getModule<Events>()->regist(event);
        m_pActor->destroy();
    }

}
