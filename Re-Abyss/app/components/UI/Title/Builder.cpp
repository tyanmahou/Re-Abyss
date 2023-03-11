#include <abyss/components/UI/Title/Builder.hpp>

#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Title/MainStream.hpp>
#include <abyss/components/UI/Title/BgmCtrl.hpp>

namespace abyss::UI::Title
{
    void Builder::Build(UIObj* pUi)
    {
        // メイン
        {
            pUi->attach<MainStream>(pUi);
        }
        // Bgm
        {
            pUi->attach<BgmCtrl>(pUi);
        }
    }
}
