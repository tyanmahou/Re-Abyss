#include <abyss/components/UI/BossHPBar/HPGaugeCtrl.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/components/Actor/Common/HP.hpp>

namespace abyss::UI::BossHPBar
{
    HPGaugeCtrl::HPGaugeCtrl(UIObj* pUi, Ref<Actor::HP> hp):
        m_pUi(pUi),
        m_hpRef(hp)
    {}
    void HPGaugeCtrl::onStart()
    {
        m_hp = 0;
        m_maxHp = static_cast<double>(m_hpRef->getMaxHp());
    }
    void HPGaugeCtrl::onUpdate()
    {
        if (!m_hpRef) {
            m_hp = 0;
            return;
        }
        m_maxHp = static_cast<double>(m_hpRef->getMaxHp());

        auto hp = static_cast<double>(m_hpRef->getHp());

        auto dt = m_pUi->getModule<GlobalTime>()->deltaTime();
        double add = m_maxHp * dt;
        if (m_hp - add >= hp) {
            m_hp -= add;
        } else if (m_hp + add <= hp) {
            m_hp += add;
        } else {
            m_hp = hp;
        }
    }
    bool HPGaugeCtrl::isFull() const
    {
        return m_hp >= m_maxHp;
    }
    bool HPGaugeCtrl::isValid() const
    {
        return static_cast<bool>(m_hpRef);
    }
}
