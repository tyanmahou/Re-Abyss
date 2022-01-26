#include <abyss/components/UI/Splash/Logo/LogoTimer.hpp>
#include <abyss/params/UI/Splash/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Splash::Logo
{
    LogoTimer::LogoTimer():
        m_timer(Param::Common::FadeTime, StartImmediately::Yes)
    {}

    double LogoTimer::time0_1() const
    {
        return m_timer.progress0_1();
    }
    bool LogoTimer::isEnd() const
    {
        return m_timer.reachedZero();
    }
}

