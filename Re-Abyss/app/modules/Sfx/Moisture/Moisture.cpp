#include <abyss/modules/Sfx/Moisture/Moisture.hpp>

namespace abyss::Sfx
{
    Moisture::Moisture()
    {
    }
    void Moisture::apply(const s3d::Texture& tex) const
    {
        m_shader.apply(tex);
    }
}
