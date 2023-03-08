#include <abyss/components/UI/Home/Top/Builder.hpp>
#include <abyss/components/UI/Home/Top/Main.hpp>
#include <abyss/components/UI/Common/FooterTips.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::Home::Top
{
    void Builder::Build(UIObj* pUi)
    {
        pUi->attach<Main>(pUi);

        pUi->attach<FooterTips>(pUi);
    }
}
