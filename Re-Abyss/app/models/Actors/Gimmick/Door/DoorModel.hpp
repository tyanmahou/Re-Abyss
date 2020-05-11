#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/types/Forward.hpp>

namespace abyss
{
    class DoorModel
    {
        s3d::Vec2 m_pos;
        s3d::Vec2 m_targetPos;
        Forward m_targetForward;
        s3d::Vec2 m_size;
    public:
        DoorModel() = default;
        DoorModel(
            const s3d::Vec2& pos, 
            const s3d::Vec2& targetPos, 
            Forward targetForward,
            const s3d::Vec2& size
        );

        const s3d::Vec2& getPos()const
        {
            return m_pos;
        }
        const s3d::Vec2& getTargetPos() const
        {
            return m_targetPos;
        }
        Forward  getTargetForward() const
        {
            return m_targetForward;
        }
        const s3d::Vec2& getSize() const
        {
            return m_size;
        }

        s3d::Vec2 fixedVisiterPos(const s3d::Vec2& visitSize) const;
    };
}