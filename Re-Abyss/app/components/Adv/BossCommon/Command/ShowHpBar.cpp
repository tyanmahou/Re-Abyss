#include <abyss/components/Adv/BossCommon/Command/ShowHpBar.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/components/Actor/Enemy/BossHpBarTarget.hpp>
#include <abyss/components/UI/BossHPBar/Builder.hpp>
#include <abyss/components/UI/BossHPBar/HPGaugeCtrl.hpp>
#include <abyss/components/Sound/SeDef.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Sound/Sounds.hpp>
#include <abyss/modules/UI/UIs.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/utils/Coro/Fiber/Wait.hpp>

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

        auto* globalTime = m_pObj->getModule<GlobalTime>();
        // ゲージ上昇
        {
            m_chargeSe = m_pObj->getModule<Sounds>()->load(Sound::SeDef::ChargeBossHp);
            m_chargeSe.play();
            while (m_hpGauge && !m_hpGauge->isFull()) {
                co_yield{};
            }
            m_chargeSe.stop();

            co_await Coro::WaitForSeconds(1.0s, globalTime);
        }
    }
}
