#include <abyss/modules/Stage/StartPos/StartPos.hpp>

namespace abyss
{
    StartPos::StartPos(
        s3d::int32 startId,
        const s3d::Vec2& pos,
        const Forward& forward,
        bool isSave
    ):
        m_startId(startId),
        m_pos(pos),
        m_forward(forward),
        m_isSave(isSave)
    {}
}
