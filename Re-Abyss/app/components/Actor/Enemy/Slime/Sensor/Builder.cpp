#include "Builder.hpp"

#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Locator.hpp>
#include <abyss/components/Actor/Common/Colliders/PointCollider.hpp>
#include <abyss/components/Actor/Common/MapCollider.hpp>
#include <abyss/components/Actor/Enemy/Slime/Sensor/MainUpdate.hpp>
#include <abyss/components/Actor/Enemy/Slime/Sensor/ParentCtrl.hpp>

namespace abyss::Actor::Enemy::Slime::Sensor
{
    void Builder::Build(ActorObj* pActor, ActorObj* parent)
    {
        pActor->attach<MainUpdate>(pActor);
        pActor->attach<ParentCtrl>(parent);

        pActor->attach<Locator>();
        pActor->attach<PointCollider>(pActor);
        pActor->attach<MapCollider>(pActor, false);
    }
}