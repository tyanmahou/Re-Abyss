#include "DecorTranslator.hpp"

#include <abyss/entities/Decor/General/CommonEntity.hpp>
#include <abyss/entities/Decor/Map/CommonEntity.hpp>

#include <abyss/entities/Actors/Map/MapEntity.hpp>

#include <abyss/components/Decor/General/Common/Builder.hpp>
#include <abyss/components/Decor/Map/Common/Builder.hpp>
#include <abyss/modules/Decor/Decor.hpp>

namespace abyss::decor
{
    Ref<DecorObj> DecorTranslator::build(Decor& decor, s3d::int32 order, const DecorEntity& entity) const
    {
#define BUILD_DECOR(buildType) if(entity.type == DecorType::##buildType) {\
    return decor.create<buildType::Builder>(order, static_cast<const buildType##Entity&>(entity)); \
}
        // General
        BUILD_DECOR(General::Common);
        
        // Map
        BUILD_DECOR(Map::Common);

        return nullptr;
    }

    std::shared_ptr<DecorEntity> DecorTranslator::toEntity(const MapEntity& map) const
    {
        auto ret = std::make_shared<Map::CommonEntity>();
        ret->id = map.id;
        ret->gId = map.gId;
        ret->type = DecorType::Map::Common;
        ret->pos = map.pos;
        ret->size = map.size;
        return ret;
    }
}