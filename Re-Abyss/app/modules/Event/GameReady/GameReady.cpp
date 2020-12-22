#include "GameReady.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/UI/UI.hpp>
#include <abyss/modules/Actors/Player/PlayerManager.hpp>

#include <abyss/components/UI/Fade/IrisOut/Builder.hpp>
#include <abyss/components/UI/Fade/IrisOut/FadeIrisOut.hpp>

namespace abyss::Event
{
    GameReady::GameReady()
    {}
    void GameReady::onStart()
    {
        auto globalTime = m_pManager->getModule<GlobalTime>();
        m_timer = TimerEx(1s, false, [globalTime] {return globalTime->timeMicroSec(); });
        m_timer.start();
        // フェードイン
        (m_fadeUI = m_pManager->getModule<UI>()->create<ui::Fade::IrisOut::Builder>()->find<ui::Fade::IrisOut::FadeIrisOut>())
            ->setIsFadeIn(true)
            ;
    }
    bool GameReady::update([[maybe_unused]]double dt)
    {
        if (m_phase == Phase::End) {
            return false;
        }
        if (auto ui = m_fadeUI) {
            auto pos = m_pManager->getModule<Actor::Player::PlayerManager>()->getPos();
            ui->setPos(pos)
                .setFadeTime(m_timer.progress0_1())
                ;
        }
        if (m_timer.reachedZero()) {
            m_phase = Phase::End;
        }
        return true;
    }
    void GameReady::onEnd()
    {
        m_fadeUI->destroy();
    }
}
