#include "WaterSurface.hpp"

namespace  abyss::Env
{
    void WaterSurface::update(double dt)
    {
        m_time += dt;
        m_view.setTime(m_time);
    }
    void WaterSurface::setActiveBack(bool isActive)
    {
        if (isActive) {
            m_activeState |= ActiveState::Back;
        } else {
            m_activeState &= ~ActiveState::Back;
        }
    }
    void WaterSurface::setActiveFront(bool isActive)
    {
        if (isActive) {
            m_activeState |= ActiveState::Front;
        } else {
            m_activeState &= ~ActiveState::Front;
        }
    }
    void WaterSurface::drawBack(const s3d::Vec2& pos) const
    {
        if ((m_activeState & ActiveState::Back) != 0) {
            m_view.drawBack(pos);
        }
    }
    void WaterSurface::drawFront(const s3d::Vec2 & pos) const
    {
        if ((m_activeState & ActiveState::Front) != 0) {
            m_view.drawFront(pos);
        }
    }
}
