#pragma once
#include <memory>
#include <abyss/controllers/UI/base/IUserInterface.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::ui::Fade
{
    class SmoothCircleVM;

    /// <summary>
    /// サークルフェード
    /// </summary>
    class SmoothCircle : public IUserInterface
    {
        s3d::Vec2 m_pos;
        double m_fadeTimeSec = 0;
        bool m_isFadeOut = true;

        std::unique_ptr<SmoothCircleVM> m_view;
    public:
        SmoothCircle();

        SmoothCircle& setPos(const s3d::Vec2& pos);
        SmoothCircle& setFadeTime(double fadeTimeSec);
        SmoothCircle& setIsFadeOut(bool isFadeOut);
        SmoothCircle& setIsFadeIn(bool isFadeIn);

        void draw() const override;
    };
}