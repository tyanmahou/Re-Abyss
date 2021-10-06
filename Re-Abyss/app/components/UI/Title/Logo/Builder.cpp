#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Title/Logo/LogoCtrl.hpp>
#include <abyss/components/UI/Title/Logo/ViewCtrl.hpp>

namespace abyss::UI::Title::Logo
{
    void Builder::Build(UIObj* pUi)
    {
        // メイン追加
        {
            pUi->attach<LogoCtrl>(pUi);
        }
        // View
        {
            pUi->attach<ViewCtrl>(pUi)->setOrder(2);
        }
    };
}