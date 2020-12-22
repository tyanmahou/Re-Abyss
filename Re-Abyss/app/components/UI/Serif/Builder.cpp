#include "Builder.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/components/UI/Serif/Main.hpp>

namespace abyss::ui::Serif
{
    void Builder::Build(IUserInterface* pUi,
        const Ref<Event::Talk::SerifModel>& serif,
        const std::shared_ptr<Event::Talk::FaceManager>& faceManager
    ) {
        // メイン追加
        {
            pUi->attach<Main>(pUi, serif, faceManager);
        }
    };
}