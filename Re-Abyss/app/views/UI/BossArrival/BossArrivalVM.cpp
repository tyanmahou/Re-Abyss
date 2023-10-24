#include <abyss/views/UI/BossArrival/BossArrivalVM.hpp>

namespace abyss::UI::BossArrival
{
    BossArrivalVM::BossArrivalVM()
    {
    }
    BossArrivalVM& BossArrivalVM::setPos(const s3d::Vec2& pos)
    {
        m_shader.setPos(pos);
        return *this;
    }
    void BossArrivalVM::draw() const
    {
        auto scoped = m_shader
            .setTime(m_timeRate)
            .start();
        s3d::Graphics2D::DrawTriangles(46 * 2 * 2);
    }
}
