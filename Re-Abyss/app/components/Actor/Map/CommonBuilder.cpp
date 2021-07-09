#include "CommonBuilder.hpp"

#include <abyss/components/Actor/Commons/TerrainProxy.hpp>
#include <abyss/components/Actor/Map/MapProxy.hpp>
#include <abyss/types/CShape.hpp>

namespace abyss::Actor::Map
{
    BuildOption::BuildOption()
    {}

    void CommonBuilder::Build(ActorObj* pActor, const BuildOption& opt)
    {
        pActor->setTag(Tag::Map{});

        // マップ情報
        auto mapProxy = pActor->attach<MapProxy>(opt.col, opt.pos, opt.size);

        // 地形
        {
            pActor->attach<TerrainProxy>(pActor)
                ->setColDirection(mapProxy->getCol())
                .setRegion(mapProxy->region())
                .setTag(opt.terrainTag)
                .setExtData(opt.terrainExtData)
                ;
        }
    }
}