#include <abyss/components/UI/BossArrival/Builder.hpp>
#include <abyss/components/UI/BossArrival/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::BossArrival
{
    void  Builder::Build(UIObj* pUi)
    {
        pUi->setFilter(Filter::Game | Filter::Event);
        pUi->attach<Main>(pUi);
    }
}
