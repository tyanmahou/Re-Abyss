#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Header/Main.hpp>
#include <abyss/modules/UI/UIOrder.hpp>

namespace abyss::UI::Header
{
    void Builder::Build(UIObj* pUi)
    {
        pUi->setOrder(UIOrder::Header);
        // メイン追加
        {
            pUi->attach<Main>(pUi);
        }
    };
}