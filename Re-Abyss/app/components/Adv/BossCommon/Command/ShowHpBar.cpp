#include <abyss/components/Adv/BossCommon/Command/ShowHpBar.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/components/Actor/Enemy/BossHpBarTarget.hpp>
#include <abyss/components/UI/BossHPBar/Builder.hpp>
#include <abyss/components/UI/BossHPBar/HPGaugeCtrl.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/UI/UIs.hpp>

namespace abyss::Adv::BossCommon
{
    ShowHpBar::ShowHpBar(AdvObj* pObj):
        m_pObj(pObj)
    {
    }
    void ShowHpBar::onStart()
    {
        m_prevUiFilter = m_pObj->getModule<UIs>()->getFilter();
        // UIレイヤーを変更
        m_pObj->getModule<UIs>()->setFilter(UI::Filter::Event);

        auto actors = m_pObj->getModule<Actors>();
        if (auto target = actors->find<Actor::Enemy::BossHpBarTarget>()) {
            if (auto hp = target->hp()) {
                auto damage = target->damageCtrl();
                auto hpBar = m_pObj->getModule<UIs>()->create<UI::BossHPBar::Builder>(hp, damage);

                m_hpGauge = hpBar->find<UI::BossHPBar::HPGaugeCtrl>();
            }
        }
    }
    void ShowHpBar::onEnd()
    {
        // UIレイヤーを戻す
        m_pObj->getModule<UIs>()->setFilter(m_prevUiFilter);

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
