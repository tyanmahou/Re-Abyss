#include <abyss/components/Actor/Land/LandProxy.hpp>
#include <Siv3D.hpp>

namespace abyss::Actor::Land
{
    LandProxy::LandProxy(
        ColDirection col,
        const s3d::Vec2& pos,
        const s3d::Vec2& size
    ) :
        m_col(col),
        m_pos(pos),
        m_size(size)
    {}

    const s3d::Vec2& LandProxy::getPos() const
    {
        return m_pos;
    }

    const s3d::Vec2& LandProxy::getSize() const
    {
        return m_size;
    }

    s3d::RectF LandProxy::region() const
    {
        return s3d::RectF{ m_pos - m_size / 2, m_size };
    }
    ColDirection LandProxy::getCol() const
    {
        return m_col;
    }
}
