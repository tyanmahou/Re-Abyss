#include "DoorDecorModel.hpp"

namespace abyss
{
    DoorDecorModel::DoorDecorModel(const s3d::Vec2& pos, const s3d::Vec2& size, DoorKind kind):
        m_pos(pos),
        m_size(size),
        m_kind(kind)
    {}
    s3d::RectF DoorDecorModel::region() const
    {
        return s3d::RectF{m_pos - m_size/2.0, m_size};
    }
    bool DoorDecorModel::isInScreen(const s3d::RectF & screen) const
    {
        return screen.intersects(this->region());
    }
}
