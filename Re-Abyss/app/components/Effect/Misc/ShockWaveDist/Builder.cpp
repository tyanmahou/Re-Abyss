#include <abyss/components/Effect/Misc/ShockWaveDist/Builder.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Misc/ShockWaveDist/DistCtrl.hpp>

namespace abyss::Effect::Misc::ShockWaveDist
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos, double radius, double power, double time)
    {
        pObj->attach<DistCtrl>(pObj, pos, radius, power, time);
    }
}