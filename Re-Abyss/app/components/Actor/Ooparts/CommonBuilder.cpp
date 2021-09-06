#include "CommonBuilder.hpp"
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/VModel.hpp>
#include <abyss/components/Actor/Ooparts/PursuitCtrl.hpp>
#include "..\Enemy\CommonBuilder.hpp"

namespace abyss::Actor::Ooparts
{
    void CommonBuilder::Build(ActorObj* pActor, ActorObj* parent)
    {
        pActor->setDestoryTiming(DestoryTiming::Never);
        pActor->setOrder(parent->getOrder() - 1);

        // ボディと追従
        {
            auto parentBody = parent->find<Body>();
            auto forward = parentBody->getForward();
            pActor->attach<Body>(pActor)
                ->initPos(parentBody->getPos() + s3d::Vec2{ forward * -20, -40 })
                .setForward(forward);

            pActor->attach<PursuitCtrl>(pActor, parentBody);
        }
        // 描画
        {
            pActor->attach<VModel>();
        }
    }
}