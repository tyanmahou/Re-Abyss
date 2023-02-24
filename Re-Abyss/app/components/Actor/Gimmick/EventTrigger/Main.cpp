#include <abyss/components/Actor/Gimmick/EventTrigger/Main.hpp>
#include <abyss/modules/Adv/Adventures.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/Temporary/Temporary.hpp>
#include <abyss/modules/Stage/Stage.hpp>

#include <abyss/components/Actor/Common/DeployId.hpp>
#include <abyss/components/Adv/AdvBuilder.hpp>
#include <abyss/components/Adv/Common/EventCtrl.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    Main::Main(ActorObj* pActor, const s3d::String& path):
        m_pActor(pActor),
        m_path(path),
        m_eventId()
    {}

    void Main::onStart()
    {
        m_eventId = m_pActor->find<DeployId>()->id();
        if (m_pActor->getModule<Temporary>()->onFlag(TempKey::EventComplete(
            m_pActor->getModule<Stage>()->mapName(),
            m_eventId
        ))) {
            // 既に完了済みなので生成しない
            m_pActor->destroy();
            return;
        }

        auto pObj = m_pActor->getModule<Adventures>()->create<Adv::AdvBuilder>(m_path);
        // イベント制御も追加
        pObj->attach<Adv::EventCtrl>(pObj.get(), m_eventId);

        m_pActor->destroy();
    }

}
