#include "WaterSurface.hpp"

namespace  abyss::Env
{
    void WaterSurface::update(double dt)
    {
        m_time += dt;
        m_view.setTime(m_time);
    }
    void WaterSurface::drawBack(const s3d::Vec2& pos) const
    {
        m_view.drawBack(pos);
    }
    void WaterSurface::drawFront(const s3d::Vec2 & pos) const
    {
        m_view.drawFront(pos);
    }
}
