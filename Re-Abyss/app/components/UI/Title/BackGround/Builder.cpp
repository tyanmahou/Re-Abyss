#include <abyss/components/UI/Title/BackGround/Builder.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Title/BackGround/BgCtrl.hpp>
#include <abyss/components/UI/Title/BackGround/ViewCtrl.hpp>

namespace abyss::UI::Title::BackGround
{
    void Builder::Build(UIObj* pUi)
    {
        // メイン追加
        {
            pUi->attach<BgCtrl>(pUi);
        }
        // View
        {
            pUi->attach<ViewCtrl>(pUi)
                ->setLayer(DrawLayer::BackGround);
        }
    };
}