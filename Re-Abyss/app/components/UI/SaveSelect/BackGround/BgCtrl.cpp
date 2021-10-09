#include "BgCtrl.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::BackGround
{
    BgCtrl::BgCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<BackGround::BackGroundVM>())
    {}
    void BgCtrl::onStart()
    {
        m_mode = m_pUi->find<Main::ModeCtrl>();
    }
    void BgCtrl::onDraw() const
    {
        bool isDeleteMode = m_mode && m_mode->is(Main::Mode::Delete);
        m_view->draw(isDeleteMode ? Palette::Red : Color(93, 93, 255));
    }
}