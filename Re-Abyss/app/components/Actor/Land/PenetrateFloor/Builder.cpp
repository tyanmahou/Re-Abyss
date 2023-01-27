#include <abyss/components/Actor/Land/PenetrateFloor/Builder.hpp>
#include <abyss/components/Actor/Land/BuilderFromEntity.hpp>
#include <abyss/components/Actor/Land/CommonBuilder.hpp>
#include <abyss/components/Actor/Land/PenetrateFloor/PenetrateFloorExtension.hpp>

namespace abyss::Actor::Land::PenetrateFloor
{
    void Builder::Build(ActorObj* pActor, const s3d::Vec2& pos, const s3d::Vec2& size, bool canDown, ColDirection aroundFloor)
    {
        // 共通
        CommonBuilder::Build(pActor, BuildOption{}
            .setPos(pos - s3d::Vec2{ 0, 17.5 })
            .setSize(size - s3d::Vec2{ 0, 35 })
            .setColDirection(ColDirection::Up)
            .setTerrainTag(Physics::Tag::PenetrateFloor{})
            .setTerrainExtData<PenetrateFloorExtension>(canDown, aroundFloor)
        );
   }
}
namespace abyss::Actor::Land
{
    template struct BuilderFromEntity<LandType::Penetrate>;
    template<>
    void BuilderFromEntity<LandType::Penetrate>::Build(ActorObj* pActor, const LandEntity& entity)
    {
        PenetrateFloor::Builder::Build(pActor, entity.pos, entity.size, entity.canDown, entity.aroundFloor);
    }
}
