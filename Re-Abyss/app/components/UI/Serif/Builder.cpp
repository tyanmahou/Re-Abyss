#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::Serif
{
    void Builder::Build(
        UIObj* pUi,
        const Ref<Novel::SerifCtrl>& serif
    )
    {
        // メイン追加
        {
            //pUi->attach<Main>(pUi, serif);
        }
    }
}