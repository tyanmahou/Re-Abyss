#include "Builder.hpp"
#include <abyss/components/Actors/God/PauseCtrl.hpp>

namespace abyss::Actor::God
{
    void Builder::Build(ActorObj* pActor)
    {
        // 死なない
        pActor->setDestoryTiming(DestoryTiming::Never);

        // ポーズ制御
        pActor->attach<PauseCtrl>(pActor);
    }
}
