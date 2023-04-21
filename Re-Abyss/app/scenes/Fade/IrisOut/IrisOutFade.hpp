#pragma once
#include <memory>
#include <abyss/scenes/Fade/ISceneFade.hpp>
#include <abyss/views/Fade/IrisOutFadeView.hpp>

namespace abyss::Fade
{
    class IrisOutFade final : public ISceneFade
    {
    public:
        IrisOutFade();

        void setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
        }
    public:
        void onFade(const s3d::RectF& rect, double t) const override;
    private:
        s3d::Vec2 m_pos;
        std::unique_ptr<IrisOutFadeView> m_view;
    };
}
