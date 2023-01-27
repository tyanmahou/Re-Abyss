#include <abyss/components/Decor/General/Common/Builder.hpp>
#include <abyss/entities/Decor/General/CommonEntity.hpp>

#include <abyss/components/Decor/BuilderFromEntity.hpp>
#include <abyss/components/Decor/Common/CommonBuilder.hpp>

namespace abyss::Decor::General::Common
{
    void Builder::Build(DecorObj* pObj, const CommonEntity& entity)
    {
        CommonBuilder::Build(pObj, BuildOption{}
            .setInitInfo(entity)
        );
    }
}
namespace abyss::Decor
{
    template struct BuilderFromEntity<DecorType::Motif::General, DecorType::General::Common>;
    template<>
    void BuilderFromEntity<DecorType::Motif::General, DecorType::General::Common>::Build(DecorObj* pDecor, const DecorEntity& entity)
    {
        General::Common::Builder::Build(pDecor, static_cast<const General::CommonEntity&>(entity));
    }
}
