#include <abyss/components/UI/Splash/Builder.hpp>
#include <abyss/components/UI/Splash/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::Splash
{
    void Builder::Build(UIObj* pUi)
    {
        // メイン処理
        {
            pUi->attach<Main>(pUi);
        }
    };
}
