#include "BackGroundModel.hpp"
#include <Siv3D.hpp>

namespace abyss::Cycle::Title::BackGround
{
    BackGroundModel::BackGroundModel():
        m_timer(10s)
    {}

    void BackGroundModel::start()
    {
        m_timer.start();
    }

    bool BackGroundModel::isStarted()
    {
        return m_timer.isRunning();
    }

    double BackGroundModel::time0_1() const
    {
        return m_timer.progress0_1();
    }
    bool BackGroundModel::isEnd() const
    {
        return m_timer.reachedZero();
    }
    s3d::Vec2 BackGroundModel::getPos() const
    {
        return EaseIn(Easing::Linear, { 480, 0 }, Scene::CenterF(), this->time0_1());
    }
}

