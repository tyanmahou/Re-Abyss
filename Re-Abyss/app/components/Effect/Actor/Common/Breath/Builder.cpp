#include <abyss/components/Effect/Actor/Common/Breath/Builder.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Common/Breath/Main.hpp>

namespace abyss::Effect::Actor::Breath
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos)
    {
        pObj->attach<Main>(pObj, pos);
    }
}