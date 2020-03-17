#include "LightModel.hpp"

namespace abyss
{
    LightModel::LightModel(const s3d::Vec2& pos, double r, double brightness):
        m_pos(pos),
        m_r(r),
        m_brightness(brightness)
    {}
}
