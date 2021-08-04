#include "WaterSarface.hpp"

namespace  abyss::Env
{
    void WaterSarface::update(double dt)
    {
        m_time += dt;
        m_view.setTime(m_time);
    }
    void WaterSarface::drawBack(const s3d::Vec2& pos) const
    {
        m_view.drawBack(pos);
    }
    void WaterSarface::drawFront(const s3d::Vec2 & pos) const
    {
        m_view.drawFront(pos);
    }
}
