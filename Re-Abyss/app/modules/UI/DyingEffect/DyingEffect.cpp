#include "DyingEffect.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/HP.hpp>
#include <abyss/views/UI/DyingEffect/DyingEffectVM.hpp>

#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/UI/UIOrder.hpp>

namespace abyss::ui
{
    DyingEffect::DyingEffect(Actor::IActor* pActor):
        m_pActor(pActor),
        m_view(std::make_unique<DyingEffectVM>())
    {
        this->m_order = UIOrder::MostBack;
    }
    void DyingEffect::start()
    {
        m_hpModel = m_pActor->find<Actor::HP>();
        m_hp = 0;
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
    }
    void DyingEffect::update([[maybe_unused]]double dt)
    {
        m_maxHp = static_cast<double>(m_hpModel->getMaxHp());
        m_hp = static_cast<double>(m_hpModel->getHp());
    
    }
    void DyingEffect::draw() const
    {
        m_view
            ->setHp(m_hp)
            .setMaxHp(m_maxHp)
            .setTime(m_pManager->getModule<GlobalTime>()->time())
            .draw();
    }
}
