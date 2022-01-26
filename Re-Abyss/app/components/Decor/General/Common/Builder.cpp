#include <abyss/components/Decor/General/Common/Builder.hpp>
#include <abyss/entities/Decor/General/CommonEntity.hpp>
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