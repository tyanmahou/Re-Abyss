#include "FooterTips.hpp"
#include <abyss/views/UI/Common/Tips/TipsView.hpp>

namespace abyss::UI
{
    FooterTips::FooterTips(const s3d::String& tips):
        m_tips(tips)
    {}

    void FooterTips::onDraw() const
    {
        TipsView::DrawFooter(m_tips);
    }
}
