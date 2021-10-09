#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/SaveSelect/UserInfo/KiraKiraCtrl.hpp>
#include <abyss/components/UI/SaveSelect/UserInfo/ViewCtrl.hpp>

namespace abyss::UI::SaveSelect::UserInfo
{
    void Builder::Build(UIObj* pUi)
    {
        pUi->attach<KiraKiraCtrl>(pUi);
        pUi->attach<ViewCtrl>(pUi);
    }
}