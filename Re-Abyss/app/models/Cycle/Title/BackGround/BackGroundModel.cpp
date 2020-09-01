#include "BackGroundModel.hpp"
#include <Siv3D.hpp>

#include <abyss/params/Cycle/Title/BgParam.hpp>

namespace abyss::Cycle::Title::BackGround
{
    BackGroundModel::BackGroundModel():
        m_timer(BgParam::Common::TimeSec)
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
        return EaseIn(Easing::Linear, Scene::CenterF(), BgParam::BackGround::EndPos, this->time0_1());
    }
    s3d::Vec2 BackGroundModel::getAtlantisPos() const
    {
        return EaseIn(Easing::Linear, BgParam::Atlantis::StartPos, Scene::CenterF(), this->time0_1());
    }
}

