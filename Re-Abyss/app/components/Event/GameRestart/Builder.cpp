#include <abyss/components/Event/GameRestart/Builder.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/components/Event/Common/GlobalTimeCtrl.hpp>
#include <abyss/components/Event/GameRestart/MainStream.hpp>

namespace abyss::Event::GameRestart
{
    void Builder::Build(EventObj* pEvent)
    {
        // 世界停止しない
        pEvent->setIsWorldStop(false);

        // メイン
        {
            pEvent->attach<MainStream>(pEvent);
        }
        // グローバルタイムスケール制御
        {
            pEvent->attach<GlobalTimeCtrl>(pEvent);
        }
    }
}
