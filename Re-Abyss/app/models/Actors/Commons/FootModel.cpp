#include "FootModel.hpp"

namespace abyss
{
    void FootModel::reset()
    {
        m_state = State::None;
        m_ladderPosX = s3d::none;

    }
    bool FootModel::isNone() const
    {
        return m_state == None;
    }
    bool FootModel::isLanding() const
    {
        return (m_state & Landing) != 0;
    }
    bool FootModel::isFloat() const
    {
        return !this->isLanding();
    }
    bool FootModel::isLadder() const
    {
        return (m_state & Ladder) != 0;
    }
    bool FootModel::isLadderTop() const
    {
        return (m_state & LadderTop) == LadderTop;
    }
    FootModel& FootModel::setLadderPosX(double posX)
    {
        m_ladderPosX = posX;
        return *this;
    }
    const s3d::Optional<double>& FootModel::getLadderPosX() const
    {
        return m_ladderPosX;
    }
    FootModel& FootModel::apply(State state)
    {
        return *this |= state;
    }
    FootModel& FootModel::operator|=(State state)
    {
        m_state = static_cast<State>(m_state | state);
        return *this;
    }
}
