#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Common/HierarchyCtrl.hpp>
#include <abyss/components/UI/SaveSelect/Main/ModeCtrl.hpp>

#include <abyss/components/UI/SaveSelect/BackGround/Builder.hpp>

namespace abyss::UI::SaveSelect::Main
{
    void Builder::Build(UIObj* pUi)
    {
        // モード制御
        pUi->attach<ModeCtrl>(pUi);

        // 背景
        BackGround::Builder::Build(pUi);
    }
}