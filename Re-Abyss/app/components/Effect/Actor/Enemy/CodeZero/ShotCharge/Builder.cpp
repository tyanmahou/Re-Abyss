#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/Builder.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/Main.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/ChargeCircle.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::ShotCharge
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos)
    {
        pObj->attach<Main>(pObj, pos);
        pObj->attach<ChargeCircle>(pObj, pos);
    }
}
