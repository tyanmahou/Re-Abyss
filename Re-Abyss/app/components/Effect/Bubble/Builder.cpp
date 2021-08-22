#include "Builder.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>

#include <abyss/components/Effect/Bubble/Main.hpp>

#include <Siv3D.hpp>

namespace abyss::Effect::Bubble
{
    void Builder::Build(EffectObj* pObj, BubbleKind kind)
    {
        const auto& offset = pObj->getModule<Camera>()->getPos();
        static constexpr Vec2 CreateRangeOffset{ -120 - 480, 260 };
        static constexpr Vec2 CreateRangeSize{ 1080,240 };
        auto basePos = s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize });
        Vec2 parallax{ 1,1 };
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
                .maxRadius = Random(10.0, 40.0),
                .basePos = basePos,
                .velocity = Vec2{0, Random(-120.0, -6.0) },
                .deflection = Random(0.0, 200.0),
                .parallax = parallax,
                .color = ColorF(0.5, 0.2),
            });
        } else if (kind == BubbleKind::Big) {
            main->setParam({
                .kind = kind,
                .maxRadius = Random(60.0, 120.0),
                .basePos = basePos,
                .velocity = Vec2{Random(-50.0, 50.0), Random(-50.0, -30.0) },
                .deflection = 0,
                .parallax = parallax,
                .color = ColorF(0.2, 0.2),
            });
        }
    }
}