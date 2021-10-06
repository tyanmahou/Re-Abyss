#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Title/Cursor/CursorCtrl.hpp>

namespace abyss::UI::Title::Cursor
{
    void Builder::Build(UIObj* pUi)
    {
        // メイン追加
        {
            pUi->attach<CursorCtrl>(pUi)->setLayer(DrawLayer::World).setOrder(3);
        }
    };
}