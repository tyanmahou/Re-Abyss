#include <abyss/components/Event/GamePause/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
#include <abyss/modules/Sound/MixBus.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>
#include <abyss/components/UI/GamePause/Main.hpp>
#include <abyss/components/UI/utils/DialogUtil.hpp>

namespace abyss::Event::GamePause
{
    MainStream::MainStream(EventObj* pEvent):
        m_pEvent(pEvent)
    {}
    void MainStream::setup(Executer executer)
    {
    }
    void MainStream::onStart()
    {
        m_pEvent->getModule<GlobalTime>()->pause();
        m_pEvent->getModule<Sfx::PostEffects>()->getBlur()->setIsValid(true);
        GlobalAudio::BusFadeVolume(MixBusKind::Bgm, 0.1, 0.2s);
    }
    void MainStream::onEnd()
    {
        m_pEvent->getModule<GlobalTime>()->resume();
        m_pEvent->getModule<Sfx::PostEffects>()->getBlur()->setIsValid(false);
        GlobalAudio::BusFadeVolume(MixBusKind::Bgm, 1, 0.5s);
    }
    Coro::Task<> MainStream::onExecute()
    {
        // 1フレーム待ち
        co_yield{};

        // ポーズ画面
        auto result = co_await UI::DialogUtil::Wait<UI::GamePause::Main>(m_pEvent);
        if (result.isContinue) {
            // ゲームを続ける
            co_return;
        } else {
            // ステージから出る
            GlobalAudio::BusFadeVolume(MixBusKind::Bgm, 1, 0.5s);
            m_pEvent->getModule<CycleMaster>()->find<Cycle::Main::Master>()->escape();

            while (true) {
                co_yield{};
            }
        }
        co_return;
    }

}
