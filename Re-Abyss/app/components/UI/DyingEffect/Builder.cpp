#include <abyss/components/UI/DyingEffect/Builder.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/components/UI/DyingEffect/Main.hpp>

namespace abyss::UI::DyingEffect
{
    void Builder::Build(UIObj* pUi, Actor::ActorObj* pActor)
    {
        // メイン追加
        {
            pUi->attach<Main>(pUi, pActor)->setOrder(DrawOrder::UI::MostBack);
        }
    }
}