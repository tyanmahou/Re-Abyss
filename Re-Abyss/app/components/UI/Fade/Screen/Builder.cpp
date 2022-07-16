#include <abyss/components/UI/Fade/Screen/Builder.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Fade/Screen/FadeCtrl.hpp>

namespace abyss::UI::Fade::Screen
{
    void Builder::Build(UIObj* pUi)
    {
        pUi->setFilter(UI::Filter::Always);

        // メイン追加
        {
            pUi->attach<FadeCtrl>(pUi)
                ->setOrder(DrawOrder::UI::Fade);
        }
    }
}
