#include "Builder.hpp"
#include <abyss/modules/Actors/base/IActor.hpp>
#include <abyss/components/Actors/Commons/Body.hpp>
#include <abyss/components/Actors/Commons/AttackerData.hpp>
#include <abyss/components/Actors/Commons/ReceiverData.hpp>
#include <abyss/components/Actors/Commons/CollisionCtrl.hpp>
#include <abyss/components/Actors/Commons/CustomCollider.hpp>

namespace abyss::Actor::Enemy::Schield::Shell
{
    void Builder::Build(IActor* pActor, IActor* parent)
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
            pActor->attach<AttackerData>(1);
        }
        // ReceiverData
        {
            pActor->attach<ReceiverData>();
        }
    }
}