#pragma once
#include <Siv3D/Timer.hpp>
#include <Siv3D/Optional.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Cycle::Title::Logo
{
    class LogoModel
    {
    public:
        enum class Phase
        {
            Start,
            Step1,
            Step2,
            Step3,
            Step4,
            Step5,
            End,
        };
        struct ViewParam
        {
            s3d::Vec2 pos;
            double alpha;
        };
    private:
        s3d::Timer m_timer;
        Phase m_phase = Phase::Start;
    public:
        LogoModel();

        void update();

        double time0_1() const;

        bool isEnd() const;

        Phase getPhase() const
        {
            return m_phase;
        }

        std::pair<s3d::Optional<ViewParam>, s3d::Optional<ViewParam>> getViewParams() const;
    };
}