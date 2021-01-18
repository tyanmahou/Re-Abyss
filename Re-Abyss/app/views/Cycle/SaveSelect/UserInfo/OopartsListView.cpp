#include "OopartsListView.hpp"
#include <Siv3D.hpp>
namespace abyss::Cycle::SaveSelect::UserInfo
{
    OopartsListView::OopartsListView()
    {
    
    }
    void OopartsListView::draw() const
    {
        for (auto&&[index, type] : s3d::Indexed(m_having)) {
            auto pos = m_pos + s3d::Vec2{ m_offsetX * (index), 0 };
            {
                ScopedColorAdd2D add(ColorF(1.0, 0));
                m_icon(type).resized(40, 40).draw(pos + Vec2{2, 2});
            }
            m_icon(type).resized(40, 40).draw(pos);
        }
    }
}
