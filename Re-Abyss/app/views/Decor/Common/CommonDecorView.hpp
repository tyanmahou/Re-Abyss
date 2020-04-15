#pragma once
#include <abyss/views/Decor/base/IDecorView.hpp>
#include <Siv3D/TexturedQuad.hpp>
namespace abyss
{
    class CommonDecorView : public IDecorView
    {
        s3d::TexturedQuad m_texturedQuad;
        s3d::Vec2 m_pos;
    public:
        CommonDecorView(const s3d::TexturedQuad& texturedQuad, const s3d::Vec2& pos);

        bool isInScreen(const s3d::RectF& screen) override;
        void draw() const;
    };
}