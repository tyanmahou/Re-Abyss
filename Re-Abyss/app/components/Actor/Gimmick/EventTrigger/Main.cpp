#include <abyss/components/Actor/Gimmick/EventTrigger/Main.hpp>
#include <abyss/modules/Novel/Novels.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Stage/Stage.hpp>

#include <abyss/components/Novel/TalkBuilder.hpp>
#include <abyss/components/Novel/Common/EventCtrl.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    Main::Main(ActorObj* pActor, const s3d::String& path, s3d::uint32 eventId):
        m_pActor(pActor),
        m_path(path),
        m_eventId(eventId)
    {}

    void Main::onStart()
    {
        if (m_pActor->getModule<Temporary>()->onFlag(TempKey::EventComplete(
            m_pActor->getModule<Stage>()->mapName(),
            m_eventId
        ))) {
            // 既に完了済みなので生成しない
            m_pActor->destroy();
            return;
        }

        auto pTalk = m_pActor->getModule<Novels>()->create<Novel::TalkBuilder>(m_path);
        // イベント制御も追加
        pTalk->attach<Novel::EventCtrl>(pTalk.get(), m_eventId);

        m_pActor->destroy();
    }

}
