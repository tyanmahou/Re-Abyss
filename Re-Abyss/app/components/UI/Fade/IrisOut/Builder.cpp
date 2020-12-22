#include "Builder.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/modules/UI/UIOrder.hpp>
#include <abyss/components/UI/Fade/IrisOut/FadeCtrl.hpp>


namespace abyss::ui::Fade::IrisOut
{
    void Builder::Build(IUserInterface* pUi)
    {
        pUi->setOrder(UIOrder::Fade);

        // メイン追加
        {
            pUi->attach<FadeCtrl>(pUi);
        }
    }
}