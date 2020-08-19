#pragma once
#include <Siv3D/Timer.hpp>

namespace abyss::Cycle::Splash::Logo
{
    class LogoModel
    {
        s3d::Timer m_timer;
    public:
        LogoModel();

        double time0_1() const;

        bool isEnd() const;
    };
}