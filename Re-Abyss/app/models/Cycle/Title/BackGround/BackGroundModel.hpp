#pragma once
#include <Siv3D/Timer.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::Title::BackGround
{
    class BackGroundModel
    {
        s3d::Timer m_timer;
    public:
        BackGroundModel();

        void start();

        bool isStarted();

        double time0_1() const;

        bool isEnd() const;

        s3d::Vec2 getPos() const;
        s3d::Vec2 getAtlantisPos() const;
    };
}