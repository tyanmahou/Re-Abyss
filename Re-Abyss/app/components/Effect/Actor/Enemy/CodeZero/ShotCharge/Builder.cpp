#include "Builder.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/ShotCharge/Main.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::ShotCharge
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos)
    {
        pObj->setTimeScale(0.333);
        pObj->attach<Main>(pObj, pos);
    }
}