#include <abyss/components/Actor/Common/Foot.hpp>

namespace abyss::Actor
{
    void Foot::reset()
    {
        m_state = State::None;
        m_ladderInfo = s3d::none;
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
    Foot& Foot::updateLadderInfo(const LadderInfo& info)
    {
        if (!m_ladderInfo) {
            m_ladderInfo = info;
        } else {
            if (m_ladderInfo->pos.y > info.pos.y) {
                m_ladderInfo->pos.y = info.pos.y;
            }
        }
        return *this;
    }
    const s3d::Optional<Foot::LadderInfo>& Foot::getLadderInfo() const
    {
        return m_ladderInfo;
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
