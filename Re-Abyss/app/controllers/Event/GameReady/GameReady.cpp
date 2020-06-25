#include "GameReady.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/UI/Fade/SmoothCircle/SmoothCircle.hpp>

namespace abyss::Event
{
    GameReady::GameReady()
    {}
    void GameReady::init()
    {
        auto globalTime = m_pManager->getModule<GlobalTime>();
        globalTime->setTimeScale(1.0);

        m_timer = TimerEx(1s, false, [globalTime] {return globalTime->timeMicroSec(); });
        m_timer.start();
        // フェードイン
        (m_fadeUI = m_pManager->getModule<UI>()->create<ui::Fade::SmoothCircle>())
            ->setIsFadeIn(true)
            ;
    }
    bool GameReady::update([[maybe_unused]]double dt)
    {
        if (m_phase == Phase::End) {
            return false;
        }
        if (auto ui = m_fadeUI) {
            auto pos = m_pManager->getModule<Player::PlayerActor>()->getPos();
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
