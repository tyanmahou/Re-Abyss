#include <abyss/components/UI/StageResult/Builder.hpp>
#include <abyss/components/UI/StageResult/Main.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>

namespace abyss::UI::StageResult
{
    void Builder::Build(UIObj* pUi)
    {
        pUi->attach<Main>(pUi);
    }
}
