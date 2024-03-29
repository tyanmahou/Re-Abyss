#pragma once
#include <memory>
#include <abyss/modules/Fade/base/ISceneFade.hpp>
#include <abyss/modules/Fade/base/IFadeColor.hpp>
#include <abyss/views/Fade/ScreenFadeView.hpp>

namespace abyss::Fade
{
    class ScreenFade final:
        public ISceneFade,
        public IFadeColor
    {
    public:
        ScreenFade();

        void setColor(const s3d::ColorF& color) override;
    public:
        void onFade(const s3d::RectF& rect, double t) const override;
    private:
        std::unique_ptr<ScreenFadeView> m_view;
    };
}
