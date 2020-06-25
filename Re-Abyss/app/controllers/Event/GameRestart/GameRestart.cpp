#include "GameRestart.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/Actors/Player/PlayerActor.hpp>
#include <abyss/controllers/UI/UI.hpp>
#include <abyss/controllers/UI/Fade/SmoothCircle/SmoothCircle.hpp>
#include <abyss/controllers/Master/Master.hpp>
namespace abyss::Event
{
    GameRestart::GameRestart():
        m_timer(2s, false)
    {}
    void GameRestart::init()
    {
        m_timer.start();
        m_fadeUI = m_pManager->getModule<UI>()->create<ui::Fade::SmoothCircle>();
    }
    bool GameRestart::update([[maybe_unused]]double dt)
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
    void GameRestart::onEnd()
    {
        m_fadeUI->destroy();
        m_pManager->getModule<Master>()->restart();
    }
}
