#include "GameRestart.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/UI/UI.hpp>
#include <abyss/modules/Master/Master.hpp>
#include <abyss/modules/Actors/Player/PlayerManager.hpp>

#include <abyss/components/UI/Fade/IrisOut/Builder.hpp>
#include <abyss/components/UI/Fade/IrisOut/FadeCtrl.hpp>

namespace abyss::Event
{
    GameRestart::GameRestart():
        m_globalTimeScale(std::make_shared<GlobalTimeScaleModel>())
    {
        m_isWorldStop = false;
    }
    void GameRestart::onStart()
    {
        auto globalTime = m_pManager->getModule<GlobalTime>();
        globalTime->addTimeScale(m_globalTimeScale);
        m_waitTimer = TimerEx(2.5s, false);
        m_fadeTimer = TimerEx(1s, false);

        m_waitTimer.start();
    }
    bool GameRestart::update([[maybe_unused]]double dt)
    {
        if (m_phase == Phase::End) {
            return false;
        }
        switch (m_phase) {
        case Phase::Wait:
        {
            m_globalTimeScale->setScale(m_waitTimer.progress0_1());
            if (m_waitTimer.reachedZero()) {
                m_fadeTimer.start();
                m_fadeUI = m_pManager->getModule<UI>()->create<ui::Fade::IrisOut::Builder>()->find<ui::Fade::IrisOut::FadeCtrl>();
                m_phase = Phase::Fade;
            }
        }
        break;
        case Phase::Fade:
        {
            if (auto ui = m_fadeUI) {
                auto pos = m_pManager->getModule<Actor::Player::PlayerManager>()->getPos();
                ui->setPos(pos)
                    .setFadeTime(m_fadeTimer.progress0_1())
                    ;
            }
            if (m_fadeTimer.reachedZero()) {
                m_phase = Phase::End;
            }
        }
        break;
        case Phase::End:
        default:
            break;
        }
        return true;
    }
    void GameRestart::onEnd()
    {
        m_fadeUI->destroy();
        m_pManager->getModule<Master>()->restart();
    }
}