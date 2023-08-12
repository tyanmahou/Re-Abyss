#include <abyss/views/UI/BossArrival/BossArrivalVM.hpp>

namespace abyss::UI::BossArrival
{
    BossArrivalVM::BossArrivalVM()
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
