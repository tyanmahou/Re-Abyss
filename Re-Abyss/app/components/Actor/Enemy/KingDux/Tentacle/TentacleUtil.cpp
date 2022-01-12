#include "TentacleUtil.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/RotateCtrl.hpp>
#include <abyss/params/Actor/Enemy/KingDux/TentacleParam.hpp>

namespace abyss::Actor::Enemy::KingDux::Tentacle
{
    s3d::Triangle TentacleUtil::Shape(const s3d::Vec2& pos, double angle)
    {
        return TentacleParam::Base::Collider
            .rotatedAt(TentacleParam::Base::RotPivot, angle)
            .moveBy(pos - TentacleParam::Base::RotPivot)
            ;
    }
    s3d::Triangle TentacleUtil::Shape(ActorObj* pActor)
    {
        return Shape(
            pActor->find<Body>()->getPos(), 
            pActor->find<RotateCtrl>()->getRotate()
        );
    }
}
