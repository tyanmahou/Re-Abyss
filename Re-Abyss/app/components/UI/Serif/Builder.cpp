#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Serif/Main.hpp>

namespace abyss::UI::Serif
{
    void Builder::Build(
        UIObj* pUi,
        const Ref<Event::Talk::SerifCtrl>& serif,
        const Ref<Event::Talk::FaceTable>& faceTable
    ) {
        // メイン追加
        {
            pUi->attach<Main>(pUi, serif, faceTable);
        }
    }
}