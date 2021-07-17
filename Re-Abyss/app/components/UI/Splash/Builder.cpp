#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Splash/Main.hpp>
#include <abyss/modules/UI/UIOrder.hpp>

namespace abyss::UI::Splash
{
    void Builder::Build(UIObj* pUi)
    {
        // メイン追加
        {
            pUi->attach<Main>(pUi);
        }

        // ロゴ
        {
            pUi->attach<Logo::LogoCtrl>(pUi);
        }
    };
}