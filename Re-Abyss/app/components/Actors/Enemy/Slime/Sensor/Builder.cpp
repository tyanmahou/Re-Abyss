#include "Builder.hpp"

#include <abyss/controllers/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/Colliders/PointCollider.hpp>
#include <abyss/components/Actors/Commons/MapCollider.hpp>
#include <abyss/components/Actors/Enemy/Slime/Sensor/MainUpdate.hpp>
#include <abyss/components/Actors/Enemy/Slime/Sensor/ParentCtrl.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
    void Builder::Build(IActor* pActor, IActor* parent)
    {
        pActor->attach<MainUpdate>(pActor);
        pActor->attach<ParentCtrl>(parent);

        pActor->attach<PointCollider>();
        pActor->attach<MapCollider>(pActor, false);
    }
}