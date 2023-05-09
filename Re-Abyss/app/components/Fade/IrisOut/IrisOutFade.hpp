#pragma once
#include <memory>
#include <abyss/modules/Fade/base/ISceneFade.hpp>
#include <abyss/modules/Fade/base/IFadeColor.hpp>
#include <abyss/views/Fade/IrisOutFadeView.hpp>

namespace abyss::Fade
{
    class IrisOutFade final :
        public ISceneFade,
        public IFadeColor
    {
    public:
        IrisOutFade();
        IrisOutFade(const s3d::Vec2& pos);

        void setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
        }
        void setColor(const s3d::ColorF& color) override;
    public:
        void onFade(const s3d::RectF& rect, double t) const override;
    private:
        s3d::Vec2 m_pos;
        std::unique_ptr<IrisOutFadeView> m_view;
    };
}
