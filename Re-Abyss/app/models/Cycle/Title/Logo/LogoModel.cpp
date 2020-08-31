#include "LogoModel.hpp"
//#include <abyss/params/Cycle/Splash/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::Cycle::Title::Logo
{
    LogoModel::LogoModel() :
        m_timer(0.5s, true)
    {}

    void LogoModel::update()
    {
        if (this->isEnd()) {
            return;
        }
        if (m_timer.reachedZero()) {
            m_phase = static_cast<Phase>(static_cast<int32>(m_phase) + 1);
        }
    }

    double LogoModel::time0_1() const
    {
        return m_timer.progress0_1();
    }
    bool LogoModel::isEnd() const
    {
        return m_phase == Phase::End;
    }
    std::pair<s3d::Optional<LogoModel::ViewParam>, s3d::Optional<LogoModel::ViewParam>> LogoModel::getViewParams() const
    {
        switch (m_phase) {
        case Phase::Step1:
        case Phase::Step2:
        case Phase::Step3:
        default:
            return { ViewParam{.pos = Scene::Center(), .alpha = 1.0}, s3d::none };
            break;
        }
    }
}

