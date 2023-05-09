#pragma once
#include <memory>
#include <abyss/components/Fade/Screen/ScreenFade.hpp>
#include <abyss/components/Fade/IrisOut/IrisOutFade.hpp>

namespace abyss::Fade
{
    class SceneFader;

    /// <summary>
    /// フェーダー
    /// SceneFaderのプロキシクラス
    /// </summary>
    class Fader
    {
    public:
        Fader(SceneFader* fader);

        std::shared_ptr<ScreenFade> fadeOutScreen(double timeSec = 1.0) const;

        std::shared_ptr<IrisOutFade> fadeInIrisOut(const s3d::Vec2& pos, double timeSec = 1.0) const;
        std::shared_ptr<IrisOutFade> fadeOutIrisOut(const s3d::Vec2& pos, double timeSec = 1.0) const;

        void fadeIn(double timeSec = 1.0) const;

        [[nodiscard]] bool isFading() const;

        void setDefaultColor(const s3d::Optional<s3d::Color>& color)
        {
            m_defaultColor = color;
        }
    private:
        SceneFader* m_fader;
        s3d::Optional<s3d::Color> m_defaultColor;
    };
}
