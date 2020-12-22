#include "Builder.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/components/UI/PlayerInfo/Main.hpp>

namespace abyss::ui::PlayerInfo
{
    void Builder::Build(IUserInterface* pUi, Actor::IActor* pActor)
    {
        // メイン追加
        {
            pUi->attach<Main>(pUi, pActor);
        }
    };
}