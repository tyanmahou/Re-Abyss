#include <abyss/components/Decor/General/SchoolOfFish/Builder.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/components/Decor/General/SchoolOfFish/Drawer.hpp>
#include <abyss/entities/Decor/General/SchoolOfFishEntity.hpp>

namespace abyss::Decor::General::SchoolOfFish
{
    void Builder::Build(DecorObj* pObj, const SchoolOfFishEntity& entity)
    {
        pObj->attach<Drawer>(pObj, entity)
            ->setLayer(entity.layer)
            .setOrder((entity.parallax.x + entity.parallax.y) / 2.0);
    }
}