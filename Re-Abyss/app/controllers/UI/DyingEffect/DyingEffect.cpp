#include "DyingEffect.hpp"
#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/models/Actors/Commons/HPModel.hpp>
#include <abyss/views/UI/DyingEffect/DyingEffectVM.hpp>

#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>
#include <abyss/controllers/UI/UIOrder.hpp>

namespace abyss::ui
{
    DyingEffect::DyingEffect(IActor* pActor):
        m_pActor(pActor),
        m_view(std::make_unique<DyingEffectVM>())
    {
        this->m_order = UIOrder::MostBack;
    }
    void DyingEffect::start()
    {
        m_hpModel = m_pActor->find<HPModel>();
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
