#include "Sky.hpp"

namespace abyss::Env
{
    void Sky::draw(const s3d::Vec2& pos) const
    {
        m_view.draw(pos);
    }
}
