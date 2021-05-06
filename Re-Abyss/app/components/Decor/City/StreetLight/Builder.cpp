#include "Builder.hpp"
#include <abyss/entities/Decor/City/StreetLightEntity.hpp>
#include <abyss/components/Decor/Commons/CommonBuilder.hpp>
#include <abyss/components/Decor/City/StreetLight/LightCtrl.hpp>
#include <abyss/modules/Decor/base/DecorObj.hpp>
namespace abyss::Decor::City::StreetLight
{
    void Builder::Build(DecorObj* pObj, const StreetLightEntity& entity)
    {
        CommonBuilder::Build(pObj, BuildOption{}
            .setInitInfo(entity)
        );

        // LightCtrl
        {
            pObj->attach<LightCtrl>(pObj)
                ->setLayer(entity.layer);
        }
    }
}