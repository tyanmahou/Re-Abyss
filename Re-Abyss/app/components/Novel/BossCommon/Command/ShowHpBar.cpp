#include <abyss/components/Novel/BossCommon/Command/ShowHpBar.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/components/Actor/Enemy/BossHpBarTarget.hpp>
#include <abyss/components/UI/BossHPBar/Builder.hpp>
#include <abyss/components/UI/BossHPBar/HPGaugeCtrl.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/UI/UIs.hpp>

namespace abyss::Novel::BossCommon
{
    ShowHpBar::ShowHpBar(TalkObj* pTalk):
        m_pTalk(pTalk)
    {
    }
    void ShowHpBar::onStart()
    {
        m_prevUiFilter = m_pTalk->getModule<UIs>()->getFilter();
        // UIレイヤーを変更
        m_pTalk->getModule<UIs>()->setFilter(UI::Filter::Event);

        auto actors = m_pTalk->getModule<Actors>();
        if (auto target = actors->find<Actor::Enemy::BossHpBarTarget>()) {
            if (auto hp = target->hp()) {
                auto damage = target->damageCtrl();
                auto hpBar = m_pTalk->getModule<UIs>()->create<UI::BossHPBar::Builder>(hp, damage);

                m_hpGauge = hpBar->find<UI::BossHPBar::HPGaugeCtrl>();
            }
        }
    }
    void ShowHpBar::onEnd()
    {
        // UIレイヤーを戻す
        m_pTalk->getModule<UIs>()->setFilter(m_prevUiFilter);

        if (m_chargeSe) {
            m_chargeSe.stop();
        }
    }
    Coro::Fiber<> ShowHpBar::onCommand()
    {
        if (!m_hpGauge) {
            co_return;
        }
        m_chargeSe = Resource::Assets::Main()->load(U"se/Common/charge_boss_hp.aas");
        m_chargeSe.play();
        while (m_hpGauge && !m_hpGauge->isFull()) {
            co_yield{};
        }
    }
}
