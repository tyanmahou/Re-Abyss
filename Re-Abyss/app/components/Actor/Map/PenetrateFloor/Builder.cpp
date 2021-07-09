#include "Builder.hpp"

#include <abyss/components/Actor/Map/CommonBuilder.hpp>
#include <abyss/components/Actor/Map/PenetrateFloor/PenetrateFloorProxy.hpp>

namespace abyss::Actor::Map::PenetrateFloor
{
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown, ColDirection aroundFloor)
    {
        // 共通
        CommonBuilder::Build(pActor, ColDirection::Up, pos - s3d::Vec2{ 0, 17.5 }, size - s3d::Vec2{ 0, 35 });

        // プロキシ
        pActor->attach<PenetrateFloorProxy>(pActor, canDown, aroundFloor);
   }
}