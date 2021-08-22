#include "Builder.hpp"
#include <abyss/modules/Event/base/IEvent.hpp>

#include <abyss/components/Event/Talk/TalkBuilder.hpp>
#include <abyss/components/Event/Talk/PlayerStateChanger.hpp>

#include <Siv3D.hpp>

namespace abyss::Event::Talk
{
    void Builder::Build(IEvent* pEvent, const s3d::String& path)
    {
        // 世界停止はしない
        pEvent->setIsWorldStop(false);

        // PlayerState制御
        {
            pEvent->attach<PlayerStateCtrl>(pEvent)
                ->setChanger<PlayerStateChanger>();
        }

        // 会話制御
        TalkBuilder::Build(pEvent, path);
    }
}