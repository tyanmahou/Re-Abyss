#include "Builder.hpp"

#include <abyss/components/Actor/Map/CommonBuilder.hpp>
#include <abyss/components/Actor/Common/ReceiverData.hpp>

namespace abyss::Actor::Map::Floor
{
    void Builder::Build(ActorObj* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size)
    {
        // 共通
        CommonBuilder::Build(pActor, BuildOption{}
            .setPos(pos)
            .setSize(size)
            .setColDirection(col)
            .setTerrainTag(Physics::Tag::Floor{})
        );


        // ReceiverData
        {
            pActor->attach<ReceiverData>();
        }
   }
}