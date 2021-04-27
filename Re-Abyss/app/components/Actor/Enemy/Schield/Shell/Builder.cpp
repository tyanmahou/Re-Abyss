#include "Builder.hpp"
#include <abyss/modules/Actor/base/ActorObj.hpp>
#include <abyss/components/Actor/Commons/Body.hpp>
#include <abyss/components/Actor/Commons/AttackerData.hpp>
#include <abyss/components/Actor/Commons/ReceiverData.hpp>
#include <abyss/components/Actor/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actor/Commons/CustomCollider.hpp>

namespace abyss::Actor::Enemy::Schield::Shell
{
    void Builder::Build(ActorObj* pActor, ActorObj* parent)
    {
        // タグ
        pActor->setTag(Tag::Enemy{} | Tag::Attacker{} | Tag::Receiver{});

        // 衝突
        {
            pActor->attach<CollisionCtrl>(pActor)
                ->setLayer(LayerGroup::Enemy);

            pActor->attach<CustomCollider>()
                ->setColFunc([body = parent->find<Body>()]()->CShape{
                    if (!body) {
                        return s3d::none;
                    }
                    return body->region();
                });
        }
        // AttackerData
        {
            pActor->attach<AttackerData>(pActor, 1);
        }
        // ReceiverData
        {
            pActor->attach<ReceiverData>();
        }
    }
}