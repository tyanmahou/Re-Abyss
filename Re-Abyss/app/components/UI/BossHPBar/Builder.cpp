#include "Builder.hpp"
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/components/UI/BossHPBar/Main.hpp>

namespace abyss::ui::BossHPBar
{
    void Builder::Build(IUserInterface* pUi, Actor::IActor* pActor)
    {
        // メイン追加
        {
            pUi->attach<Main>(pUi, pActor);
        }
    };
}