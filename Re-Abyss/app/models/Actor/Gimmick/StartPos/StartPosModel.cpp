#include "StartPosModel.hpp"

namespace abyss
{
    StartPosModel::StartPosModel(
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
