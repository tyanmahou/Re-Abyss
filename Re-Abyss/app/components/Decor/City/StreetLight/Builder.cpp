#include <abyss/components/Decor/City/StreetLight/Builder.hpp>

#include <abyss/entities/Decor/City/StreetLightEntity.hpp>

#include <abyss/components/Decor/BuilderFromEntity.hpp>
#include <abyss/components/Decor/Common/CommonBuilder.hpp>
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
namespace abyss::Decor
{
    template struct BuilderFromEntity<DecorType::Motif::City, DecorType::City::StreetLight>;
    template<>
    void BuilderFromEntity<DecorType::Motif::City, DecorType::City::StreetLight>::Build(DecorObj* pDecor, const DecorEntity& entity)
    {
        City::StreetLight::Builder::Build(pDecor, static_cast<const City::StreetLightEntity&>(entity));
    }
}
