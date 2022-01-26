#include <abyss/components/Decor/Common/CommonBuilder.hpp>

#include <abyss/modules/Decor/base/DecorObj.hpp>
#include <abyss/components/Decor/Common/DecorInfo.hpp>
#include <abyss/components/Decor/Common/BasicDraw.hpp>

namespace abyss::Decor
{
    void CommonBuilder::Build(DecorObj* pObj, const BuildOption& opt)
    {
        // 装飾情報
        pObj->attach<DecorInfo>(pObj, opt.entity);

        // 基本描画
        if (opt.isEnableBasicDraw) {
            pObj->attach<BasicDraw>(pObj)
                ->setLayer(opt.entity.layer)
                .setOrder((opt.entity.parallax.x + opt.entity.parallax.y) / 2.0);
        }
    }
}