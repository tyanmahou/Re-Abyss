#include <abyss/components/UI/BossHPBar/HPGaugeCtrl.hpp>
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/components/Actor/Common/HP.hpp>

namespace abyss::UI::BossHPBar
{
    HPGaugeCtrl::HPGaugeCtrl(Actor::ActorObj* pActor):
        m_pActor(pActor)
    {}
    void HPGaugeCtrl::onStart()
    {
        m_hpModel = m_pActor->find<Actor::HP>();
        m_hp = 0;
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
    }
    void HPGaugeCtrl::onUpdate()
    {
        if (!m_hpModel) {
            m_hp = 0;
            return;
        }
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());

        auto hp = static_cast<double>(m_hpModel->getHp());

        auto dt = m_pActor->getModule<GlobalTime>()->deltaTime();
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
        return static_cast<bool>(m_hpModel);
    }
}
