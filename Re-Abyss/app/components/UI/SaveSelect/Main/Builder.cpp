#include <abyss/components/UI/SaveSelect/Main/Builder.hpp>

#include <abyss/commons/MsgUtil.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Common/FooterTips.hpp>

#include <abyss/components/UI/SaveSelect/Main/ModeCtrl.hpp>
#include <abyss/components/UI/SaveSelect/Main/SelectFrameCtrl.hpp>
#include <abyss/components/UI/SaveSelect/Main/UserSelector.hpp>
#include <abyss/components/UI/SaveSelect/Main/Users.hpp>

#include <abyss/components/UI/SaveSelect/BackGround/Builder.hpp>
#include <abyss/components/UI/SaveSelect/UserInfo/Builder.hpp>

namespace abyss::UI::SaveSelect::Main
{
    void Builder::Build(UIObj* pUi)
    {
        // ユーザー制御
        pUi->attach<Users>(pUi);
        pUi->attach<UserSelector>(pUi);

        // モード制御
        pUi->attach<ModeCtrl>(pUi);
        pUi->attach<SelectFrameCtrl>(pUi);

        // フッター
        {
            pUi->attach<FooterTips>(pUi)
                ->setTips(U"Z…{} X…{}"_fmt(
                MsgUtil::Decide,
                MsgUtil::Cancel
            ));
        }

        // 背景
        BackGround::Builder::Build(pUi);

        // インフォ
        UserInfo::Builder::Build(pUi);
    }
}
