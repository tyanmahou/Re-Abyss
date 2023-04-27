#include <abyss/components/Event/GameClear/MainStream.hpp>
#include <abyss/commons/Path.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/components/Event/FadeUtil.hpp>

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
        m_pEvent->getModule<Sound>()->play(Path::SoundPath + U"bgm/Main/Common/clear.aas", 0s);
        // 少し待つ
        co_await Coro::WaitForSeconds(3.42s);

        // フェード
        co_await FadeUtil::WaitOutIrisOutByPlayerPos(m_pEvent->getManager());

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
