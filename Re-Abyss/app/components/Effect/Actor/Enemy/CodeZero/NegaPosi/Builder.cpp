#include <abyss/components/Effect/Actor/Enemy/CodeZero/NegaPosi/Builder.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/NegaPosi/Main.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::NegaPosi
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos)
    {
        pObj->attach<Main>(pObj, pos);
    }
}
