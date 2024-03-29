#include <abyss/components/UI/PlayerInfo/Builder.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/PlayerInfo/Main.hpp>

namespace abyss::UI::PlayerInfo
{
    void Builder::Build(UIObj* pUi, Actor::ActorObj* pActor)
    {
        // メイン追加
        {
            pUi->attach<Main>(pUi, pActor);
        }
    };
}