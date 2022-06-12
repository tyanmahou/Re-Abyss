#pragma once
#include <abyss/commons/Fwd.hpp>
#include <Siv3D/Timer.hpp>

namespace abyss::UI::Splash::Logo
{
    class LogoTimer
    {
    public:
        LogoTimer(UIObj* pUi);

        double time0_1() const;

        bool isEnd() const;
    private:
        s3d::Timer m_timer;
    };
}
