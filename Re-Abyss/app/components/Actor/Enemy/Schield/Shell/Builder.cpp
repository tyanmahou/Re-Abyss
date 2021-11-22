#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Common/Body.hpp>

#include <abyss/components/Actor/Common/ColCtrl.hpp>
#include <abyss/components/Actor/Common/Collider.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Attacker.hpp>
#include <abyss/components/Actor/Common/Col/Extension/Receiver.hpp>


namespace abyss::Actor::Enemy::Schield::Shell
{
    // TODO Main 統合
    void Builder::Build(ActorObj* pActor, ActorObj* parent)
    {
        // タグ
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{});

        // 衝突
        {
            auto collider = pActor->attach<Collider>();
            collider->add([
                body = pActor->find<Body>()
            ]()->CShape {
               if (!body) {
                   return s3d::none;
               }
               return body->region();
            });

            pActor->attach<ColCtrl>(pActor)
                ->addBranch()
                ->addNode<Col::Node>(collider->main())
                .setLayer(ColSys::LayerGroup::Enemy)
                .attach<Col::Attacker>(pActor, 1)
                .attach<Col::Receiver>(pActor);
        }
    }
}