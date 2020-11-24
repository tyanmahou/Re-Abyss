#pragma once
#include <memory>
#include <abyss/controllers/UI/base/IUserInterface.hpp>
#include <abyss/utils/Ref/Ref.hpp>

namespace abyss::ui::Fade
{
    class IrisOutVM;

    /// <summary>
    /// サークルフェード
    /// </summary>
    class IrisOut : public IUserInterface
    {
        s3d::Vec2 m_pos;
        double m_fadeTimeSec = 0;
        bool m_isFadeOut = true;

        std::unique_ptr<IrisOutVM> m_view;
    public:
        IrisOut();

        IrisOut& setPos(const s3d::Vec2& pos);
        IrisOut& setFadeTime(double fadeTimeSec);
        IrisOut& setIsFadeOut(bool isFadeOut);
        IrisOut& setIsFadeIn(bool isFadeIn);

        void draw() const override;
    };
}