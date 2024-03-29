#pragma once
#include <memory>
#include <abyss/modules/Fade/SceneFader.hpp>
#include <abyss/modules/Fade/base/IFadeColor.hpp>
#include <abyss/utils/Ref/Ref.hpp>

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

        template<class T>
        Ref<T> set() requires std::constructible_from<T>
        {
            auto fade = std::make_shared<T>();
            m_fader->set(fade);
            if constexpr (std::derived_from<T, IFadeColor>) {
                if (m_defaultColor) {
                    fade->setColor(*m_defaultColor);
                }
            }
            return fade;
        }
        template<class T>
        Ref<T> fadeIn(double timeSec = 1.0) requires std::constructible_from<T>
        {
            fadeIn(timeSec);
            return set<T>();
        }
        template<class T>
        Ref<T> fadeOut(double timeSec = 1.0) requires std::constructible_from<T>
        {
            fadeOut(timeSec);
            return set<T>();
        }
        void fadeIn(double timeSec = 1.0) const;
        void fadeOut(double timeSec = 1.0) const;
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
