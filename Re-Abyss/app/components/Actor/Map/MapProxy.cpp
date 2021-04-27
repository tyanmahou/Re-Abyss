#include "MapProxy.hpp"
#include <Siv3D.hpp>
#include <abyss/types/MapColInfo.hpp>

namespace abyss::Actor::Map
{
    MapProxy::MapProxy(
        ColDirection col,
        const s3d::Vec2& pos,
        const s3d::Vec2& size
    ) :
        m_col(col),
        m_pos(pos),
        m_size(size)
    {}

    const s3d::Vec2& MapProxy::getPos() const
    {
        return m_pos;
    }

    const s3d::Vec2& MapProxy::getSize() const
    {
        return m_size;
    }

    s3d::RectF MapProxy::region() const
    {
        return s3d::RectF{ m_pos - m_size / 2, m_size };
    }
    ColDirection MapProxy::getCol() const
    {
        return m_col;
    }
    MapColInfo MapProxy::getMapColInfo() const
    {
        return {
            .region = this->region(),
            .col = m_col
        };
    }
}
