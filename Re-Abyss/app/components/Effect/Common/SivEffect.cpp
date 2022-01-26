#include <abyss/components/Effect/Common/SivEffect.hpp>

namespace abyss::Effect
{
    SivEffect::SivEffect(std::unique_ptr<s3d::IEffect>&& effect):
        m_effect(std::move(effect))
    {}

    bool SivEffect::onDraw(double time)
    {
       return m_effect->update(time);
    }
}
