#include "BackGroundModel.hpp"
#include <Siv3D.hpp>

namespace abyss::Cycle::Title::BackGround
{
    BackGroundModel::BackGroundModel():
        m_timer(10s)
    {}

    double BackGroundModel::time0_1() const
    {
        return m_timer.progress0_1();
    }
    bool BackGroundModel::isEnd() const
    {
        return m_timer.reachedZero();
    }
}

