#include "Foot.hpp"

namespace abyss::Actor
{
    void Foot::reset()
    {
        m_state = State::None;
        m_ladderPosX = s3d::none;

    }
    bool Foot::isNone() const
    {
        return m_state == None;
    }
    bool Foot::isLanding() const
    {
        return (m_state & Landing) != 0;
    }
    bool Foot::isFloat() const
    {
        return !this->isLanding();
    }
    bool Foot::isLadder() const
    {
        return (m_state & Ladder) != 0;
    }
    bool Foot::isLadderTop() const
    {
        return (m_state & LadderTop) == LadderTop;
    }
    bool Foot::isDownable() const
    {
        return (m_state & Downable) != 0;
    }
    Foot& Foot::setLadderPosX(double posX)
    {
        m_ladderPosX = posX;
        return *this;
    }
    const s3d::Optional<double>& Foot::getLadderPosX() const
    {
        return m_ladderPosX;
    }
    Foot& Foot::apply(State state)
    {
        return *this |= state;
    }
    Foot& Foot::operator|=(State state)
    {
        m_state = static_cast<State>(m_state | state);
        return *this;
    }
}
