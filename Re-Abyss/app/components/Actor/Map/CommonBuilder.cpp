#include "CommonBuilder.hpp"

#include <abyss/components/Actor/Commons/TerrainProxy.hpp>
#include <abyss/components/Actor/Map/MapProxy.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss::Actor::Map
{
    void CommonBuilder::Build(ActorObj* pActor, ColDirection col, const s3d::Vec2& pos, const s3d::Vec2& size)
    {
        pActor->setTag(Tag::Map{});

        // マップ情報
        auto mapProxy = pActor->attach<MapProxy>(col, pos, size);

        // 地形
        {
            pActor->attach<TerrainProxy>(pActor)
                ->setColDirection(mapProxy->getCol())
                .setRegion(mapProxy->region());
        }
    }
}