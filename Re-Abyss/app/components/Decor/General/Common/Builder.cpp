#include "Builder.hpp"
#include <abyss/entities/Decor/General/CommonEntity.hpp>
#include <abyss/components/Decor/Commons/CommonBuilder.hpp>

namespace abyss::Decor::General::Common
{
    void Builder::Build(DecorObj* pObj, const CommonEntity& entity)
    {
        CommonBuilder::Build(pObj, BuildOption{}
            .setInitInfo(entity)
        );
    }
}