#include <abyss/modules/Sfx/Bloom/Bloom.hpp>

namespace abyss::Sfx
{
    Bloom::Bloom()
    {
    }
    void Bloom::apply(const s3d::Texture& tex) const
    {
        m_bloomShader.apply(tex);
    }
}
