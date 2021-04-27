#include "DecorTranslator.hpp"

#include <abyss/entities/Decor/General/CommonEntity.hpp>
#include <abyss/entities/Decor/City/StreetLightEntity.hpp>
#include <abyss/entities/Decor/Map/CommonEntity.hpp>

#include <abyss/components/Decor/General/Common/Builder.hpp>
#include <abyss/components/Decor/City/StreetLight/Builder.hpp>
#include <abyss/components/Decor/Map/TileMap/Builder.hpp>
#include <abyss/modules/Decor/Decors.hpp>

namespace abyss::decor
{
    Ref<DecorObj> DecorTranslator::build(Decors& decor, s3d::int32 order, const DecorEntity& entity) const
    {
#define BUILD_DECOR(buildType) if(entity.type == DecorType::##buildType) {\
    return decor.create<buildType::Builder>(order, static_cast<const buildType##Entity&>(entity)); \
}
        // General
        BUILD_DECOR(General::Common);

        // City
        BUILD_DECOR(City::StreetLight);

        return nullptr;
    }

    Ref<DecorObj> DecorTranslator::build(Decors& decor, s3d::int32 order, const Map::TileMapModel& tileMap) const
    {
        return decor.create<Map::TileMap::Builder>(order, tileMap);
    }
}