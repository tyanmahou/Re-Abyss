#include "DoorModel.hpp"

namespace abyss
{
    DoorModel::DoorModel(
        const s3d::Vec2& pos, 
        const s3d::Vec2& targetPos, 
        Forward targetForward, 
        const s3d::Vec2& size
    ):
        m_pos(pos),
        m_targetPos(targetPos),
        m_targetForward(targetForward),
        m_size(size)
    {}

    s3d::Vec2 DoorModel::fixedVisiterPos(const s3d::Vec2 & visitSize) const
    {
        s3d::Vec2 ret = m_pos;
        ret.y += (m_size.y - visitSize.y) / 2.0;
        return ret;
    }


}
