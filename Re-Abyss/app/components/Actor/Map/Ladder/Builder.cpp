#include <abyss/components/Actor/Map/Ladder/Builder.hpp>

#include <abyss/components/Actor/Map/CommonBuilder.hpp>

namespace abyss::Actor::Map::Ladder
{
    void Builder::Build(ActorObj* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size)
    {
        // 共通
        CommonBuilder::Build(pActor, BuildOption{}
            .setPos(pos)
            .setSize(size)
            .setColDirection(col)
            .setTerrainTag(Physics::Tag::Ladder{})
        );
   }
}