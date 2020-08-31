#pragma once
#include <Siv3D/Timer.hpp>

namespace abyss::Cycle::Title::BackGround
{
    class BackGroundModel
    {
        s3d::Timer m_timer;
    public:
        BackGroundModel();

        double time0_1() const;

        bool isEnd() const;
    };
}