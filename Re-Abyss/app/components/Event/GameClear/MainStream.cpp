#include <abyss/components/Event/GameClear/MainStream.hpp>
#include <abyss/components/Sound/BgmDef.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Fade/FadeUtil.hpp>

#include <abyss/components/Cycle/Main/Master.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

#include <Siv3D.hpp>

namespace abyss::Event::GameClear
{
    MainStream::MainStream(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void MainStream::setup(Executer executer)
    {
    }
    void MainStream::onStart()
    {
        m_pEvent->getModule<UIs>()->setFilter(UI::Filter::Adv);
    }
    void MainStream::onEnd()
    {
    }
    Coro::Fiber<> MainStream::onExecute()
    {
        // クリアBGM
        m_pEvent->getModule<Sounds>()->play(Sound::BgmDef::StageResult, 0s);
        // 少し待つ
        co_await Coro::WaitForSeconds(3.42s);

        // フェード
        co_await FadeOut::WaitIrisOutByPlayerPos(m_pEvent);

        // リスタート
        m_pEvent->getModule<CycleMaster>()
            ->find<Cycle::Main::Master>()
            ->clear();

        m_pEvent->getModule<UIs>()->setFilter(UI::Filter::Always);

        while (true) {
            co_yield{};
        }
    }
}
