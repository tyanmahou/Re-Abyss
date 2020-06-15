#include "ChargeBossHPBar.hpp"
#include <Siv3D.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/Sound/Sound.hpp>
#include <abyss/commons/ResourceManager/ResourceManager.hpp>
#include <abyss/controllers/UI/UI.hpp>
namespace abyss::Event::Talk
{
    void ChargeBossHPBar::init()
    {
        m_pManager->getModule<UI>()->setActiveAll(false);
        m_hpBar->setActive(true);
        if (m_bossBgmPath) {
            m_pManager->getModule<Sound>()->stop(0s);
        }
        m_se = ResourceManager::Main()
            ->loadAudio(U"se/commons/charge_boss_hp.ogg");
    }

    bool ChargeBossHPBar::update([[maybe_unused]]double dt)
    {
        if (!m_hpBar) {
            return false;
        }
        if (m_timer.update()) {
            m_se.playOneShot(0.4);
        }
        return !m_hpBar->isFull();
    }

    ChargeBossHPBar::ChargeBossHPBar(Ref<ui::BossHPBar> hpBar):
        m_hpBar(hpBar),
        m_timer(0.05s, true)
    {}

    ChargeBossHPBar::~ChargeBossHPBar()
    {
        if (auto path = m_bossBgmPath) {
            m_pManager->getModule<Sound>()->play(Path::SoundPath + *path, 0s);
        }
        m_pManager->getModule<UI>()->setActiveAll(true);
    }

}
