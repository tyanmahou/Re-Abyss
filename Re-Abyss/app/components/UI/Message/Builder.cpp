#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Message/Main.hpp>

namespace abyss::UI::Message
{
    void Builder::Build(
        UIObj* pUi,
        const Ref<Novel::Engine>& engine
    )
    {
        pUi->setFilter(Filter::Always);

        // メイン追加
        {
            pUi->attach<Main>(pUi, engine);
        }
    }
}