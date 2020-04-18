#include "MapDecorModel.hpp"

namespace abyss
{
    MapDecorModel::MapDecorModel(s3d::uint32 gId, const s3d::RectF& rect):
        m_gId(gId),
        m_rect(rect)
    {}

    bool MapDecorModel::isInScreen(const s3d::RectF& screen)const
    {
        return screen.intersects(m_rect);
    }
}
