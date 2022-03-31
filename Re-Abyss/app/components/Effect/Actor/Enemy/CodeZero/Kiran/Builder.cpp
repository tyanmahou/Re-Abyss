#include <abyss/components/Effect/Actor/Enemy/CodeZero/Kiran/Builder.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Enemy/CodeZero/Kiran/Main.hpp>

namespace abyss::Effect::Actor::Enemy::CodeZero::Kiran
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos)
    {
        pObj->attach<Main>(pObj, pos);
    }
}