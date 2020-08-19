#include "LogoModel.hpp"
#include <Siv3D.hpp>

namespace abyss::Cycle::Splash::Logo
{
    LogoModel::LogoModel():
        m_timer(1s, true)
    {}

    double LogoModel::time0_1() const
    {
        return m_timer.progress0_1();
    }
    bool LogoModel::isEnd() const
    {
        return m_timer.reachedZero();
    }
}

