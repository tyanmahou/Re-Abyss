#include <abyss/components/UI/Common/FooterTips.hpp>
#include <abyss/views/UI/Common/Tips/TipsView.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI
{
    FooterTips::FooterTips(UIObj* pUi):
        m_pUi(pUi)
    {
        this->setOrder(DrawOrder::UI::Footer);
    }
    void FooterTips::onUpdate()
    {
        m_timer.update(m_pUi->deltaTime());
    }
    void FooterTips::onDraw() const
    {
        TipsView::DrawFooter(m_tips, m_timer.rate());
    }
}
