#include "Builder.hpp"
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/UI/UIOrder.hpp>
#include <abyss/components/UI/DyingEffect/Main.hpp>

namespace abyss::UI::DyingEffect
{
    void Builder::Build(UIObj* pUi, Actor::ActorObj* pActor)
    {
        pUi->setOrder(UIOrder::MostBack);

        // メイン追加
        {
            pUi->attach<Main>(pUi, pActor);
        }
    }
}