#include <abyss/components/Actor/God/Builder.hpp>

namespace abyss::Actor::God
{
    void Builder::Build(ActorObj* pActor)
    {
        // 死なない
        pActor->setDestoryTiming(DestoryTiming::Never);
    }
}
