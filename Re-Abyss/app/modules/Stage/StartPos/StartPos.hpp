#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/values/Forward.hpp>

namespace abyss
{
    class StartPos
    {
    public :
        StartPos() = default;
        StartPos(
            s3d::int32 startId, 
            const s3d::Vec2& pos, 
            const Forward& forward,
            bool isSave
        );

        s3d::int32 getStartId() const
        {
            return m_startId;
        }
        const s3d::Vec2& getPos() const
        {
            return m_pos;
        }

        Forward getForward() const
        {
            return m_forward;
        }
        bool isSave() const
        {
            return m_isSave;
        }
    private:
        s3d::int32 m_startId = -1;
        s3d::Vec2 m_pos{ 0, 0 };
        Forward m_forward{ Forward::Right()};
        bool m_isSave = true;
    };
}
