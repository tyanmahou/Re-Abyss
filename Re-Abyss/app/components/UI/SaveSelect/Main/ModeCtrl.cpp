#include <abyss/components/UI/SaveSelect/Main/ModeCtrl.hpp>

#include <abyss/commons/FontName.hpp>
#include <abyss/commons/Msg/Manager.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::Main
{
    ModeCtrl::ModeCtrl(UIObj* pUi):
        m_pUi(pUi)
    {}
    void ModeCtrl::onDraw() const
    {
        if (m_mode == Mode::GameStart) {
            FontAsset(FontName::SceneName)(U"- {} -"_fmt(Msg::Text(U"SaveSelect", U"Mode_GameStart"))).drawAt(AnchorUtil::FromTc(0, 50), Color(0, 255, 255));
        } else {
            FontAsset(FontName::SceneName)(U"- {} -"_fmt(Msg::Text(U"SaveSelect", U"Mode_Delete"))).drawAt(AnchorUtil::FromTc(0, 50), Color(255, 0, 0));
        }
    }
}
