#include "LightModel.hpp"

namespace abyss
{
    LightModel::LightModel(const s3d::Vec2& pos, double range, double brightness):
        m_pos(pos),
        m_range(range),
        m_brightness(brightness)
    {}
}
