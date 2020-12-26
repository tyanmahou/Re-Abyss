#include "MainStream.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>

#include <abyss/modules/Event/Events.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/modules/UI/UI.hpp>

#include <abyss/components/UI/BossHPBar/Main.hpp>
#include <abyss/utils/Coro/Wait/Wait.hpp>

#include <Siv3D.hpp>

namespace abyss::Event::CreateBossHPBar
{
    MainStream::MainStream(IEvent* pEvent, const Ref<ui::IUserInterface>& hpBar) :
        m_pEvent(pEvent),
        m_hpBar(hpBar)
    {}

    void MainStream::onStart()
    {
        // UI非表示
        m_pEvent->getModule<UI>()->setActiveAll(false);
        m_hpBar->setActive(true);
        if (m_bossBgmPath) {
            m_pEvent->getModule<Sound>()->stop(0s);
        }
        m_se = Resource::Assets::Main()
            ->loadAudio(U"se/commons/charge_boss_hp.ogg");
    }

    Coro::Task<> MainStream::onExecute()
    {
        auto hpGauge = m_hpBar->find<ui::BossHPBar::HPGaugeCtrl>();
        while (hpGauge && !hpGauge->isFull()) {
            m_se.playOneShot(0.4);
            co_yield Coro::WaitForSeconds(0.05s);
        }
        co_return;
    }

    void MainStream::onEnd()
    {
        if (auto path = m_bossBgmPath) {
            m_pEvent->getModule<Sound>()->play(Path::SoundPath + *path, 0s);
        }
        m_pEvent->getModule<UI>()->setActiveAll(true);
    }

}