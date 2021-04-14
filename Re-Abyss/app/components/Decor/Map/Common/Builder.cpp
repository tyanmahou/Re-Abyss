#include "Builder.hpp"
#include <abyss/entities/Decor/Map/CommonEntity.hpp>
#include <abyss/components/Decor/Commons/CommonBuilder.hpp>
#include <abyss/components/Decor/Map/MapDraw.hpp>

#include <abyss/modules/Decor/base/DecorObj.hpp>

namespace abyss::decor::Map::Common
{
    void Builder::Build(DecorObj* pObj, const CommonEntity& entity)
    {
        CommonBuilder::Build(pObj, BuildOption{}
            .setInitInfo(entity)
            .setIsEnableBasicDraw(false)
        );

        pObj->attach<MapDraw>(pObj);
    }
}