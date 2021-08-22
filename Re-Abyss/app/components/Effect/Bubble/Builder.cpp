#include "Builder.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

#include <abyss/components/Effect/Bubble/Main.hpp>

#include <Siv3D.hpp>

namespace abyss::Effect::Bubble
{
    RectF BaseRect(EffectObj* pObj)
    {
        if (auto room = pObj->getModule<RoomManager>()) {
            return room->currentRoom().getRegion();
        }
        return pObj->getModule<Camera>()->screenRegion();
    }
    RectF ParallaxedRect(EffectObj* pObj, const Vec2& parallax)
    {
        auto base = BaseRect(pObj);

    }
    void Builder::Build(EffectObj* pObj, BubbleKind kind)
    {
        double rand0_1 = Random();
        Vec2 parallax{ 1,1 };
        if (kind == BubbleKind::Middle) {
            parallax.x = parallax.y = Math::Lerp(1.0, 1.5, rand0_1);
        } else if (kind == BubbleKind::Big) {
            parallax.x = parallax.y = Math::Lerp(0.4, 0.9, rand0_1);
        }
        const auto& offset = pObj->getModule<Camera>()->getPos();
        static constexpr Vec2 CreateRangeOffset{ -120 - 480, 260 };
        static constexpr Vec2 CreateRangeSize{ 1080,240 };
        auto basePos = s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize });
        
        auto main = pObj->attach<Main>(pObj);
        if (kind == BubbleKind::Small) {
            main->setParam({
                .kind = kind,
                .maxRadius = 1,
                .basePos = basePos,
                .velocity = Vec2{0, Random(-72.0, -36.0) },
                .deflection = Random(0.0, 400.0),
                .parallax = parallax,
                .color = ColorF(0.8, 0.5),
            });
        } else if (kind == BubbleKind::Middle) {
            main->setParam({
                .kind = kind,
                .maxRadius = Math::Lerp(10.0, 40.0, rand0_1),
                .basePos = basePos,
                .velocity = Vec2{0, Math::Lerp(-6.0, -120.0, rand0_1)},
                .deflection = Math::Lerp(10.0, 200.0, rand0_1),
                .parallax = parallax,
                .color = ColorF(0.5, 0.2),
            });
        } else if (kind == BubbleKind::Big) {
            main->setParam({
                .kind = kind,
                .maxRadius = Math::Lerp(120.0, 60.0, rand0_1),
                .basePos = basePos,
                .velocity = Vec2{Math::Lerp(1.0, 50.0, rand0_1) * RandomBool() ? 1.0 : -1.0, Math::Lerp(-30, -50.0, rand0_1) },
                .deflection = 0,
                .parallax = parallax,
                .color = ColorF(0.2, 0.2),
            });
        }
    }
}