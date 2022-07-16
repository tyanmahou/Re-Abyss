#include <abyss/components/Event/GamePause/MainStream.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/Sfx/PostEffects.hpp>
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
    }
    void MainStream::onEnd()
    {
        m_pEvent->getModule<GlobalTime>()->resume();
        m_pEvent->getModule<Sfx::PostEffects>()->getBlur()->setIsValid(false);
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
        }
        co_return;
    }

}
