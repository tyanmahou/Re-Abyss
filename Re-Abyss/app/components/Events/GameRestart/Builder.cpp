#include "Builder.hpp"

#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/components/Events/Common/GlobalTimeCtrl.hpp>
#include <abyss/components/Events/Common/FadeIrisOut.hpp>
#include <abyss/components/Events/GameRestart/MainStream.hpp>

namespace abyss::Event::GameRestart
{
    void Builder::Build(IEvent* pEvent)
    {
        // 世界停止しない
        pEvent->setIsWorldStop(false);

        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
        // フェード制御
        {
            pEvent->attach<FadeIrisOut>(pEvent, false);
        }
        // グローバルタイムスケール制御
        {
            pEvent->attach<GlobalTimeCtrl>(pEvent);
        }
    }
}