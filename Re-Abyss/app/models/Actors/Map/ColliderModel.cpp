#include "ColliderModel.hpp"

namespace abyss::Map
{
    ColliderModel::ColliderModel(
        IActor* pActor, 
        const s3d::Vec2& pos, 
        const s3d::Vec2& size
    ):
        IColliderModel(pActor),
        m_pos(pos),
        m_size(size)
    {}

    const s3d::Vec2& ColliderModel::getPos() const
    {
        return m_pos;
    }

    const s3d::Vec2& ColliderModel::getSize() const
    {
        return m_size;
    }

    s3d::RectF ColliderModel::region() const
    {
        return s3d::RectF{ m_pos - m_size / 2, m_size };
    }

    CShape ColliderModel::getCollider() const
    {
        return this->region();
    }

}
