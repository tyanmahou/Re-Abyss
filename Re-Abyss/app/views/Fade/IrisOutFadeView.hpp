#pragma once
#include <abyss/views/Fade/FadeViewBase.hpp>
#include <abyss/views/Shader/Mask/MaskShader.hpp>

namespace abyss::Fade
{
    class IrisOutFadeView final : public FadeViewBase
    {
    public:
        IrisOutFadeView();

        void draw(double t, const s3d::Vec2& pos, const s3d::RectF& rect) const;
    private:
        MaskShader m_maskShader;
    };
}
