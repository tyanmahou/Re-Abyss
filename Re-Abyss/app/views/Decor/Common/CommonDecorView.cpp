#include "CommonDecorView.hpp"

namespace abyss
{
    CommonDecorView::CommonDecorView(const s3d::TexturedQuad& texturedQuad, const s3d::Vec2& pos):
        m_texturedQuad(texturedQuad),
        m_pos(pos)
    {    
    }
    bool CommonDecorView::isInScreen(const s3d::RectF& screen)
    {
        auto drawRegion = m_texturedQuad.quad.movedBy(m_pos - m_texturedQuad.center);
        return screen.intersects(drawRegion);
    }

    void CommonDecorView::draw() const
    {
        m_texturedQuad.drawAt(m_pos);
    }

}
