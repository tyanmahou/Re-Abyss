#pragma once
#include <memory>
#include <abyss/scenes/Fade/ISceneFade.hpp>
#include <abyss/views/Fade/ScreenFadeView.hpp>

namespace abyss::Fade
{
    class ScreenFade final: public ISceneFade
    {
    public:
        ScreenFade();

        void setColor(const s3d::Color& color) const;
    public:
        void onFade(const s3d::RectF& rect, double t) const override;
    private:
        std::unique_ptr<ScreenFadeView> m_view;
    };
}
