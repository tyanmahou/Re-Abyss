#include "MapParamModel.hpp"
#include <Siv3D.hpp>

namespace abyss::Map
{
    MapParamModel::MapParamModel(
        const s3d::Vec2& pos,
        const s3d::Vec2& size
    ) :
        m_pos(pos),
        m_size(size)
    {}

    const s3d::Vec2& MapParamModel::getPos() const
    {
        return m_pos;
    }

    const s3d::Vec2& MapParamModel::getSize() const
    {
        return m_size;
    }

    s3d::RectF MapParamModel::region() const
    {
        return s3d::RectF{ m_pos - m_size / 2, m_size };
    }
}
