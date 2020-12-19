#include "Builder.hpp"
#include <abyss/components/Actors/Gimmick/EventTrigger/Main.hpp>

namespace abyss::Actor::Gimmick::EventTrigger
{
    void Builder::Build(IActor* pActor, const s3d::FilePath& path)
    {
        pActor->attach<Main>(pActor, path);
    }
}