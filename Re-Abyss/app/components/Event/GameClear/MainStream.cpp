#include <abyss/components/Event/GameClear/MainStream.hpp>
#include <abyss/commons/Path.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/FieldEnv/Environment.hpp>
#include <abyss/modules/Fade/Fader.hpp>

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
        {
            auto* env = m_pEvent->getModule<Environment>();
            auto* playerManager = m_pEvent->getModule<Actor::Player::PlayerManager>();
            auto* fader = m_pEvent->getModule<Fader>();
            auto* camera = m_pEvent->getModule<Camera>();
            auto fade = fader->fadeOutIrisOut(camera->transform(playerManager->getPos()));
            fade->setColor(env->getThemeColorOrDefault());
            while (fader->isFading()) {
                fade->setPos(camera->transform(playerManager->getPos()));
                co_yield{};
            }
        }

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
