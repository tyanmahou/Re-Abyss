#include "CommonBuilder.hpp"
#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/components/Decor/Commons/DecorInfo.hpp>
#include <abyss/components/Decor/Commons/BasicDraw.hpp>

namespace abyss::Decor
{
    void CommonBuilder::Build(DecorObj* pObj, const BuildOption& opt)
    {
        // 装飾情報
        pObj->attach<DecorInfo>(pObj, opt.entity);

        // 基本描画
        if (opt.isEnableBasicDraw) {
            pObj->attach<BasicDraw>(pObj);
        }
    }
}