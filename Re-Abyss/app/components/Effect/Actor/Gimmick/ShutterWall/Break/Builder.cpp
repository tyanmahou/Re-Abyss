#include <abyss/components/Effect/Actor/Gimmick/ShutterWall/Break/Builder.hpp>

#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/components/Effect/Actor/Gimmick/ShutterWall/Break/Main.hpp>

namespace abyss::Effect::Actor::Gimmick::ShutterWall::Break
{
    void Builder::Build(EffectObj* pObj, const s3d::Vec2& pos)
    {
        pObj->attach<Main>(pObj, pos);
    }
}
