#pragma once
#include <memory>
#include <abyss/modules/Fade/SceneFader.hpp>
#include <abyss/modules/Fade/base/IFadeColor.hpp>

namespace abyss::Fade
{
    /// <summary>
    /// フェーダー
    /// SceneFaderのプロキシクラス
    /// </summary>
    class Fader
    {
    public:
        Fader(SceneFader* fader);

        template<class T, class... Args>
        std::shared_ptr<T> fadeIn(Args&&... args, double timeSec = 1.0) requires std::constructible_from<T, Args...>
        {
            auto fade = std::make_shared<T>(std::forward<Args...>(args)...);
            m_fader->set(fade).fadeIn(timeSec);
            if constexpr (std::derived_from<T, IFadeColor>) {
                fade->setColor(*m_defaultColor);
            }
            return fade;
        }
        template<class T, class... Args>
        std::shared_ptr<T> fadeOut(Args&&... args, double timeSec = 1.0) requires std::constructible_from<T, Args...>
        {
            auto fade = std::make_shared<T>(std::forward<Args...>(args)...);
            m_fader->set(fade).fadeOut(timeSec);
            if constexpr (std::derived_from<T, IFadeColor>) {
                fade->setColor(*m_defaultColor);
            }
            return fade;
        }
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
