#include "Builder.hpp"
#include <abyss/components/Actors/God/PauseCtrl.hpp>

namespace abyss::Actor::God
{
    void Builder::Build(IActor* pActor)
    {
        // 死なない
        pActor->setIsDontDestoryOnLoad();

        // ポーズ制御
        pActor->attach<PauseCtrl>(pActor);
    }
}
