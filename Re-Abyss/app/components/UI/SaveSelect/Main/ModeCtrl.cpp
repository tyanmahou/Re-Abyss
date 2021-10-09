#include "ModeCtrl.hpp"

#include <abyss/commons/FontName.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>
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
            FontAsset(FontName::SceneName)(U"- データ選択 -").drawAt(PivotUtil::FromTc(0, 50), Color(0, 255, 255));
        } else {
            FontAsset(FontName::SceneName)(U"- データ削除 -").drawAt(PivotUtil::FromTc(0, 50), Color(255, 0, 0));
        }
    }
}
