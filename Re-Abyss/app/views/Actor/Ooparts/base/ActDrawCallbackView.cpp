#include "ActDrawCallbackView.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Effect/Effects.hpp>

namespace abyss::Actor::Ooparts
{
    ActDrawCallbackView::ActDrawCallbackView(Manager* manager):
        m_pManager(manager)
    {}
    void ActDrawCallbackView::onAddEffect(std::unique_ptr<s3d::IEffect>&& effect) const
    {
        auto* effects = m_pManager->getModule<Effects>();
        effects->regist(std::move(effect), Effect::EffectLayer::WorldBack);
    }
}
