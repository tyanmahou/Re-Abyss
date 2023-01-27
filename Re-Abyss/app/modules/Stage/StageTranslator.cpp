#include "StageTranslator.hpp"

#include <abyss/modules/Actor/Actors.hpp>
#include <abyss/modules/Decor/Decors.hpp>

#include <abyss/entities/Actor/Enemy/EnemyEntity.hpp>
#include <abyss/entities/Actor/Gimmick/GimmickEntity.hpp>
#include <abyss/entities/Actor/Item/ItemEntity.hpp>
#include <abyss/entities/Actor/Land/LandEntity.hpp>
#include <abyss/utils/Reflection/Reflection.hpp>

// TODO リフレクション化
#include <abyss/components/Actor/Land/Floor/Builder.hpp>
#include <abyss/components/Actor/Land/PenetrateFloor/Builder.hpp>
#include <abyss/components/Actor/Land/Ladder/Builder.hpp>

#include <abyss/entities/Decor/General/CommonEntity.hpp>
#include <abyss/entities/Decor/General/SchoolOfFishEntity.hpp>
#include <abyss/entities/Decor/City/StreetLightEntity.hpp>
#include <abyss/entities/Decor/Map/CommonEntity.hpp>

#include <abyss/components/Decor/General/Common/Builder.hpp>
#include <abyss/components/Decor/General/SchoolOfFish/Builder.hpp>
#include <abyss/components/Decor/City/StreetLight/Builder.hpp>
#include <abyss/components/Decor/Map/TileMap/Builder.hpp>

namespace abyss
{
    using namespace Actor;
    using namespace Actor::Enemy;
    Ref<Actor::ActorObj> StageTranslator::Build(Actors& actors, const EnemyEntity& entity)
    {
        if (auto builder = Reflect<>::find<void(ActorObj*, const EnemyEntity&)>(
            U"abyss::Actor::Enemy::BuilderFromEntity<{}>::Build"_fmt(static_cast<s3d::int32>(entity.type))
            )) {
            auto obj = actors.create();
            builder(obj.get(), entity);
            return obj;
        }
        return nullptr;
    }

    using namespace Actor::Gimmick;
    Ref<Actor::ActorObj> StageTranslator::Build(Actors& actors, const GimmickEntity& entity)
    {
        switch (entity.type) {
        case GimmickType::StartPos: return nullptr;
        case GimmickType::BgmChanger: return nullptr;
        default:
            break;
        }

        if (auto builder = Reflect<>::find<void(ActorObj*, const GimmickEntity&)>(
            U"abyss::Actor::Gimmick::BuilderFromEntity<{}>::Build"_fmt(static_cast<s3d::int32>(entity.type))
            )) {
            auto obj = actors.create();
            builder(obj.get(), entity);
            return obj;
        }
        return nullptr;
    }

    using namespace Actor::Item;
    Ref<Actor::ActorObj> StageTranslator::Build(Actors& actors, const ItemEntity& entity)
    {
        if (auto builder = Reflect<>::find<void(ActorObj*, const ItemEntity&)>(
            U"abyss::Actor::Item::BuilderFromEntity<{}>::Build"_fmt(static_cast<s3d::int32>(entity.type))
            )) {
            auto obj = actors.create();
            builder(obj.get(), entity);
            return obj;
        }
        return nullptr;
    }

    using namespace Actor::Land;
    Ref<Actor::ActorObj> StageTranslator::Build(Actors& actors, const LandEntity& entity)
    {
        using namespace Actor::Land;
        if (entity.type == LandType::Floor) {
            return actors.create<Floor::Builder>(entity.col, entity.pos, entity.size);
        }
        if (entity.type == LandType::Ladder) {
            return actors.create<Ladder::Builder>(entity.col, entity.pos, entity.size);
        }
        if (entity.type == LandType::Penetrate) {
            return actors.create<PenetrateFloor::Builder>(entity.pos, entity.size, entity.canDown, entity.aroundFloor);
        }
        return nullptr;
    }

    using namespace Decor;
    Ref<DecorObj> StageTranslator::Build(Decors& decor, const DecorEntity& entity)
    {
#define BUILD_DECOR(buildType) if(entity.type == DecorType::##buildType) {\
    return decor.create<buildType::Builder>(static_cast<const buildType##Entity&>(entity)); \
}
        // General
        BUILD_DECOR(General::Common);
        BUILD_DECOR(General::SchoolOfFish);

        // City
        BUILD_DECOR(City::StreetLight);

        return nullptr;
    }

    Ref<DecorObj> StageTranslator::Build(Decors& decor, const Map::TileMapData& tileMap)
    {
        return decor.create<Map::TileMap::Builder>(tileMap);
    }
}
