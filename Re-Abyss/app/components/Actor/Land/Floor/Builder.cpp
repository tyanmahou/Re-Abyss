#include <abyss/components/Actor/Land/Floor/Builder.hpp>

#include <abyss/components/Actor/Land/CommonBuilder.hpp>

namespace abyss::Actor::Land::Floor
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
   }
}
