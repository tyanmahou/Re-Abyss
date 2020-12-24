#include "Builder.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/components/UI/Serif/Main.hpp>

namespace abyss::ui::Serif
{
    void Builder::Build(IUserInterface* pUi, Event::Talk::TalkObj* pTalk) {
        // メイン追加
        {
            pUi->attach<Main>(pUi, pTalk);
        }
    }
}