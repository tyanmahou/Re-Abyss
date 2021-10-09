#include "BgCtrl.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    BgCtrl::BgCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<BackGround::BackGroundVM>())
    {}
    void BgCtrl::onStart()
    {
        m_mode = m_pUi->find<ModeCtrl>();
    }
    void BgCtrl::onDraw() const
    {
        m_view->draw(m_mode->is(Mode::Delete) ? Palette::Red : Color(93, 93, 255));
    }
}