#include "MapDecorView.hpp"

namespace abyss
{
    MapDecorView::MapDecorView(const s3d::TextureRegion& textureRegion, const s3d::Vec2& pos):
        m_textureRegion(textureRegion),
        m_pos(pos)
    {}

    bool MapDecorView::isInScreen(const s3d::RectF & screen)
    {
        s3d::RectF drawRegion{ m_pos, m_textureRegion.size };
        return screen.intersects(drawRegion);
    }

    void MapDecorView::draw() const
    {
        m_textureRegion.draw(m_pos);
    }

}
