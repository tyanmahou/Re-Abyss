#include <abyss/components/Actor/Land/CommonBuilder.hpp>

#include <abyss/components/Actor/Common/TerrainProxy.hpp>
#include <abyss/components/Actor/Land/LandProxy.hpp>
#include <abyss/utils/Collision/CShape.hpp>

namespace abyss::Actor::Land
{
    BuildOption::BuildOption()
    {}

    void CommonBuilder::Build(ActorObj* pActor, const BuildOption& opt)
    {
        // マップ情報
        auto mapProxy = pActor->attach<LandProxy>(opt.col, opt.pos, opt.size);

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
