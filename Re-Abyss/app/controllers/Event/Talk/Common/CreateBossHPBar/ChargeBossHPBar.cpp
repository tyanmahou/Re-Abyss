#include "ChargeBossHPBar.hpp"
#include <Siv3D.hpp>

namespace abyss::Event::Talk
{
    void ChargeBossHPBar::init()
    {
    }

    bool ChargeBossHPBar::update([[maybe_unused]]double dt)
    {
        if (!m_hpBar) {
            return false;
        }
        if (m_timer.update()) {
            static Audio se(U"resources/sounds/se/commons/charge_boss_hp.ogg");
            se.playOneShot(0.4);
        }
        return !m_hpBar->isFull();
    }

    ChargeBossHPBar::ChargeBossHPBar(Ref<ui::BossHPBar> hpBar):
        m_hpBar(hpBar),
        m_timer(0.05s, true)
    {}

}
