#include "Builder.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/modules/UI/UIOrder.hpp>
#include <abyss/components/UI/DyingEffect/Main.hpp>

namespace abyss::ui::DyingEffect
{
    void Builder::Build(IUserInterface* pUi, Actor::IActor* pActor)
    {
        pUi->setOrder(UIOrder::MostBack);

        // メイン追加
        {
            pUi->attach<Main>(pUi, pActor);
        }
    };
}