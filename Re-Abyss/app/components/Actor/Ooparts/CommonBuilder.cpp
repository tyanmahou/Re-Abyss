﻿#include <abyss/components/Actor/Ooparts/CommonBuilder.hpp>
#include <abyss/components/Actor/Common/Body.hpp>
#include <abyss/components/Actor/Common/VModel.hpp>
#include <abyss/components/Actor/Common/BossFadeMask.hpp>
#include <abyss/components/Actor/Ooparts/PursuitCtrl.hpp>
#include <abyss/components/Actor/Ooparts/KiraKiraCtrl.hpp>

namespace abyss::Actor::Ooparts
{
    void CommonBuilder::Build(ActorObj* pActor, ActorObj* parent)
    {
        pActor->setDestoryTiming(DestoryTiming::Never);

        // ボディと追従
        {
            auto parentBody = parent->find<Body>();
            auto forward = parentBody->getForward();
            pActor->attach<Body>(pActor)
                ->initPos(parentBody->getCenterPos() + s3d::Vec2{ forward.signH() * -20, -40 })
                .setForward(forward);

            pActor->attach<PursuitCtrl>(pActor, parentBody);
        }
        // キラキラエフェクト
        {
            pActor->attach<KiraKiraCtrl>(pActor);
        }
        // 描画
        {
            auto parentLayer = DrawLayer::World;
            auto parentOrder = DrawOrder::World::Default;
            if (auto parentVModel = parent->find<VModel>()) {
                parentLayer = parentVModel->getLayer();
                parentOrder = parentVModel->getOrder();
            }
            pActor->attach<VModel>()
                ->setLayer(parentLayer)
                .setOrder(parentOrder - 0.1);
        }
        // BossFadeMask
        {
            pActor->attach<BossFadeMask>(pActor)
                ->setDrawer<BossFadeMaskFromMainVModel>(pActor)
                ;
        }
    }
}
