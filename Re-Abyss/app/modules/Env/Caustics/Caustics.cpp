#include <abyss/modules/Env/Caustics/Caustics.hpp>

namespace  abyss::Env
{
    void Caustics::update(double dt)
    {
        m_time += dt;
        m_view.setTime(m_time);
    }
    void Caustics::setActiveBack(bool isActive)
    {
        if (isActive) {
            m_activeState |= ActiveState::Back;
        } else {
            m_activeState &= ~ActiveState::Back;
        }
    }
    void Caustics::setActiveFront(bool isActive)
    {
        if (isActive) {
            m_activeState |= ActiveState::Front;
        } else {
            m_activeState &= ~ActiveState::Front;
        }
    }
    void Caustics::drawBack(const s3d::Vec2& pos) const
    {
        if ((m_activeState & ActiveState::Back) != 0) {
            m_view.drawBack(pos);
        }
    }
    void Caustics::drawFront(const s3d::Vec2 & pos) const
    {
        if ((m_activeState & ActiveState::Front) != 0) {
            m_view.drawFront(pos);
        }
    }
}
