#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/PlayerInfo/Main.hpp>

namespace abyss::UI::PlayerInfo
{
    void Builder::Build(UIObj* pUi, Actor::IActor* pActor)
    {
        // メイン追加
        {
            pUi->attach<Main>(pUi, pActor);
        }
    };
}