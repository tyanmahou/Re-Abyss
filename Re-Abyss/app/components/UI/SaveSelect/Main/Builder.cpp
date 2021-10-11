#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Common/HierarchyCtrl.hpp>
#include <abyss/components/UI/Common/FooterTips.hpp>

#include <abyss/components/UI/SaveSelect/Main/ModeCtrl.hpp>
#include <abyss/components/UI/SaveSelect/Main/SelectFrameCtrl.hpp>
#include <abyss/components/UI/SaveSelect/Main/UserSelector.hpp>
#include <abyss/components/UI/SaveSelect/Main/Users.hpp>

#include <abyss/components/UI/SaveSelect/BackGround/Builder.hpp>
#include <abyss/components/UI/SaveSelect/UserInfo/Builder.hpp>

#include <abyss/components/UI/SaveSelect/Main/Hierarchy/UserSelect.hpp>

namespace abyss::UI::SaveSelect::Main
{
    void Builder::Build(UIObj* pUi)
    {
        // 階層制御
        pUi->attach<HierarchyCtrl>(pUi)
            ->push<UserSelect>(pUi);

        // ユーザー制御
        pUi->attach<Users>(pUi);
        pUi->attach<UserSelector>(pUi);

        // モード制御
        pUi->attach<ModeCtrl>(pUi);
        pUi->attach<SelectFrameCtrl>(pUi);

        // フッター
        {
            pUi->attach<FooterTips>(U"Z…決定 X…キャンセル");
        }

        // 背景
        BackGround::Builder::Build(pUi);

        // インフォ
        UserInfo::Builder::Build(pUi);
    }
}