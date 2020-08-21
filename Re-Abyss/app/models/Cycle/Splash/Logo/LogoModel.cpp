#include "LogoModel.hpp"
#include <abyss/params/Cycle/Splash/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Cycle::Splash::Logo
{
    LogoModel::LogoModel():
        m_timer(Param::Common::FadeTime, true)
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

