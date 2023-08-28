#include <abyss/views/UI/BossArrival/BossArrivalVM.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>

namespace abyss::UI::BossArrival
{
    BossArrivalVM::BossArrivalVM():
        m_pos(AnchorUtil::FromCc(0 ,0))
    {
    }
    BossArrivalVM& BossArrivalVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }
    void BossArrivalVM::draw() const
    {
    }
}
