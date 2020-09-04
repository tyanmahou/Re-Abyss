#include "MapParam.hpp"
#include <Siv3D.hpp>

namespace abyss::Actor::Map
{
    MapParam::MapParam(
        const s3d::Vec2& pos,
        const s3d::Vec2& size
    ) :
        m_pos(pos),
        m_size(size)
    {}

    const s3d::Vec2& MapParam::getPos() const
    {
        return m_pos;
    }

    const s3d::Vec2& MapParam::getSize() const
    {
        return m_size;
    }

    s3d::RectF MapParam::region() const
    {
        return s3d::RectF{ m_pos - m_size / 2, m_size };
    }
}
