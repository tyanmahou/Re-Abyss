#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/Serif/Main.hpp>

namespace abyss::UI::Serif
{
    void Builder::Build(
        UIObj* pUi,
        const Ref<Novel::SerifCtrl>& serif,
        const Ref<Novel::FaceTable>& faceTable
    ) {
        // メイン追加
        {
            pUi->attach<Main>(pUi, serif, faceTable);
        }
    }
}