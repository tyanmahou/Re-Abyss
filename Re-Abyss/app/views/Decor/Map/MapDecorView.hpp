#pragma once
#include <Siv3D/TextureRegion.hpp>

#include <abyss/views/Decor/base/IDecorView.hpp>
namespace abyss
{
    class MapDecorView : public IDecorView
    {
        s3d::TextureRegion m_textureRegion;
        s3d::Vec2 m_pos;
    public:
        MapDecorView(const s3d::TextureRegion& textureRegion, const s3d::Vec2& pos);

        bool isInScreen(const s3d::RectF& screen) override;
        void draw() const;
    };
}