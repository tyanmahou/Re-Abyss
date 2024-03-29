#include <abyss/components/Actor/Gimmick/Door/DoorData.hpp>

namespace abyss::Actor::Gimmick::Door
{
    DoorData::DoorData(
        s3d::int32 startId,
        const s3d::Vec2& pos,
        const s3d::Vec2& targetPos,
        Forward targetForward,
        const s3d::Vec2& size,
        DoorKind kind,
        bool isSave
    ):
        m_startId(startId),
        m_pos(pos),
        m_targetPos(targetPos),
        m_targetForward(targetForward),
        m_size(size),
        m_kind(kind),
        m_isSave(isSave)
    {}

    s3d::Vec2 DoorData::fixedVisiterPos(const s3d::Vec2 & visitSize) const
    {
        s3d::Vec2 ret = m_pos;
        ret.y += (m_size.y - visitSize.y) / 2.0;
        return ret;
    }


}
