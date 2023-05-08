#pragma once
#include <memory>
#include <abyss/scenes/Fade/ISceneFade.hpp>
#include <abyss/utils/TimeLite/Timer.hpp>

namespace abyss::Fade
{
    /// <summary>
    /// シーンフェード
    /// </summary>
    class SceneFader
    {
    public:
        SceneFader();
        ~SceneFader();

        SceneFader& set(std::shared_ptr<ISceneFade> fade);
        void fadeIn(double timeSec = 1.0);
        void fadeOut(double timeSec = 1.0);

        [[nodiscard]] bool isFading() const;

        void update(double dt);
        void draw() const;
    private:
        std::shared_ptr<ISceneFade> m_fade;
        TimeLite::Timer m_timer;
        bool m_isFadeIn = true;
    };
}
