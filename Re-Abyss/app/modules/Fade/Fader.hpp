#pragma once
#include <memory>
#include <abyss/scenes/Fade/Screen/ScreenFade.hpp>
#include <abyss/scenes/Fade/IrisOut/IrisOutFade.hpp>

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
    private:
        SceneFader* m_fader;
    };
}
