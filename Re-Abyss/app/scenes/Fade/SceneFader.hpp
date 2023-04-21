#pragma once
#include <memory>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Fade
{
    class ISceneFade
    {
    public:
        virtual ~ISceneFade() = default;
        virtual void onFade(const s3d::RectF& rect, double t) const= 0;
    };

    /// <summary>
    /// シーンフェード
    /// </summary>
    class SceneFader
    {
    public:
        SceneFader();
        ~SceneFader();

        SceneFader& set(std::shared_ptr<ISceneFade> fade);
        void fadeIn(double timeSec);
        void fadeOut(double timeSec);

        bool isFading() const;

        void update(double dt);
        void draw() const;
    private:
        std::shared_ptr<ISceneFade> m_fade;
        TimeLite::Timer m_timer;
        bool m_isFadeIn = true;
    };
}
