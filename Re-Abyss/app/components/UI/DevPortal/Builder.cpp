#include <abyss/components/UI/DevPortal/Builder.hpp>
#if ABYSS_DEVELOP
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/DevPortal/Main.hpp>

namespace abyss::UI::DevPortal
{
    void Builder::Build(UIObj* pUi)
    {
        // メイン追加
        {
            pUi->attach<Main>(pUi);
        }
    };
}
#endif
