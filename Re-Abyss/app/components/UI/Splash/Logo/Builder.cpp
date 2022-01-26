#include <abyss/components/UI/Splash/Logo/Builder.hpp>
#include <abyss/components/UI/Splash/Logo/LogoCtrl.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::Splash::Logo
{
    void Builder::Build(UIObj* pUi)
    {
        // ロゴ
        {
            pUi->attach<LogoCtrl>(pUi);
        }
    };
}