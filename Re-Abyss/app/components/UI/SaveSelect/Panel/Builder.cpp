#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Common/HierarchyCtrl.hpp>
#include <abyss/components/UI/Common/FooterTips.hpp>
#include <abyss/components/UI/SaveSelect/Panel/Hierarchy/UserSelect.hpp>

namespace abyss::UI::SaveSelect::Panel
{
    void Builder::Build(UIObj* pUi)
    {
        pUi->attach<HierarchyCtrl>(pUi)
            ->push<UserSelect>(pUi);

        pUi->attach<FooterTips>(U"Z…決定 X…キャンセル");
    }
}