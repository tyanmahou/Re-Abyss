#include "Builder.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/components/UI/Serif/Main.hpp>

namespace abyss::ui::Serif
{
    void Builder::Build(
        IUserInterface* pUi,
        const Ref<Event::Talk::SerifCtrl>& serif,
        const Ref<Event::Talk::FaceTable>& faceTable
    ) {
        // メイン追加
        {
            pUi->attach<Main>(pUi, serif, faceTable);
        }
    }
}