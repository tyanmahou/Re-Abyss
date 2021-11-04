#include "Builder.hpp"
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Event/Talk/MainStream.hpp>
#include <abyss/components/Event/Talk/PlayerStateChanger.hpp>

#include <Siv3D.hpp>

namespace abyss::Event::Talk
{
    void Builder::Build(
        EventObj* pEvent,
        const s3d::String& path,
        const Ref<Actor::ILocator>& pTargetLocator
    ) {
        // 世界停止はしない
        pEvent->setIsWorldStop(false);

        // PlayerState制御
        {
            pEvent->attach<PlayerStateCtrl>(pEvent)
                ->setChanger<PlayerStateChanger>(pTargetLocator);
        }

        // 会話制御
        {
            pEvent->attach<MainStream>(pEvent, path);
        }
    }
}