#include <abyss/components/UI/Common/FooterTips.hpp>
#include <abyss/views/UI/Common/Tips/TipsView.hpp>

namespace abyss::UI
{
    FooterTips::FooterTips(UIObj* pUi):
        m_pUi(pUi)
    {
        this->setOrder(DrawOrder::UI::Footer);
    }

    void FooterTips::onDraw() const
    {
        TipsView::DrawFooter(m_tips);
    }
}
