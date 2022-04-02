#include <abyss/components/Effect/Actor/Common/EnemyDead/Builder.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Common/EnemyDead/Main.hpp>

namespace abyss::Effect::Actor::EnemyDead
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos)
    {
        pObj->attach<Main>(pObj, pos);
    }
}