#include "SimpleDrawCallbackView.hpp"

namespace abyss::Actor::Ooparts
{
    SimpleDrawCallbackView::SimpleDrawCallbackView(TimeGetFunction_t clock):
        m_effect(clock)
    {}

    void SimpleDrawCallbackView::update() const
    {
        m_effect.update();
    }

    void SimpleDrawCallbackView::onAddEffect(std::unique_ptr<s3d::IEffect> && effect) const
    {
        m_effect.add(std::move(effect));
    }
}
