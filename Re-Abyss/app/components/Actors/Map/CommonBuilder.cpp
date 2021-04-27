#include "CommonBuilder.hpp"

#include <abyss/components/Actors/Commons/Terrain.hpp>
#include <abyss/components/Actors/Map/MapProxy.hpp>
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
            pActor->attach<Terrain>(pActor)
                ->setMapColInfo(mapProxy->getMapColInfo());
        }
    }
}