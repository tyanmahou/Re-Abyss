#include "Builder.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Ooparts/Common/KiraKira/Main.hpp>

namespace abyss::Effect::Actor::Ooparts::KiraKira
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos, Type type)
    {
        pObj->attach<Main>(pObj, pos, type);
    }
}