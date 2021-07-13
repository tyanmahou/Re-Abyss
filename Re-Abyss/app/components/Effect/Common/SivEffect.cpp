#include "SivEffect.hpp"

namespace abyss::Effect
{
    SivEffect::SivEffect(std::unique_ptr<s3d::IEffect>&& effect):
        m_effect(std::move(effect))
    {}

    void SivEffect::onDraw(double time)
    {
        m_isEnd = !m_effect->update(time);
    }
}
