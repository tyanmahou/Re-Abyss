#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    class DoorModel
    {
        s3d::Vec2 m_pos;
        s3d::Vec2 m_targetPos;
        s3d::Vec2 m_size;
    public:
        DoorModel() = default;
        DoorModel(const s3d::Vec2& pos, const s3d::Vec2& targetPos, const s3d::Vec2& size);

        const s3d::Vec2& getPos()const
        {
            return m_pos;
        }
        const s3d::Vec2& getTargetPos() const
        {
            return m_targetPos;
        }
        const s3d::Vec2& getSize() const
        {
            return m_size;
        }

        s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize) const;
    };
}