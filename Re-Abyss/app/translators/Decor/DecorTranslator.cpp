#include "DecorTranslator.hpp"

#include <abyss/entities/Decor/General/CommonEntity.hpp>

#include <abyss/components/Decor/General/Common/Builder.hpp>
#include <abyss/modules/Decor/Decor.hpp>

namespace abyss::decor
{
    Ref<DecorObj> DecorTranslator::build(Decor& decor, s3d::int32 order, const DecorEntity& entity)
    {
#define BUILD_DECOR(buildType) if(entity.type == DecorType::##buildType) {\
    return decor.create<buildType::Builder>(order, static_cast<const buildType##Entity&>(entity)); \
}
        BUILD_DECOR(General::Common);

        return nullptr;
    }
}