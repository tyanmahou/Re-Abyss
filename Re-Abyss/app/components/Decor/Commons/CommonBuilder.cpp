#include "CommonBuilder.hpp"
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/components/Decor/Commons/DecorInfo.hpp>

namespace abyss::decor
{
    void CommonBuilder::Build(DecorObj* pObj, const BuildOption& opt)
    {
        // 装飾情報
        pObj->attach<DecorInfo>(pObj, opt.entity);
    }
}