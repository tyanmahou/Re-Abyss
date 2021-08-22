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
    void Builder::Build(EffectObj* pObj, BubbleKind kind, LayerKind layer)
    {
        double rand0_1 = Random();
        Main::Param param{};
        param.kind = kind;
        if (layer == LayerKind::Front) {
            param.parallax.x = param.parallax.y = Math::Lerp(1.0, 1.5, rand0_1);
            param.velocity.x = 0;
            param.velocity.y = Math::Lerp(-20.0, -120.0, rand0_1);
            param.deflection = Math::Lerp(10.0, 200.0, rand0_1);
            param.color = ColorF(0.5, s3d::Math::Lerp(0.1, 0.05, rand0_1));
        } else if (layer == LayerKind::Back) {
            param.parallax.x = param.parallax.y = Math::Lerp(0.4, 0.9, rand0_1);
            param.velocity.x = Math::Lerp(2.0, 50.0, rand0_1) * (RandomBool() ? 1.0 : -1.0);
            param.velocity.y = Math::Lerp(-30, -50.0, rand0_1);
            param.deflection = 0;
            param.color = ColorF(0.2, s3d::Math::Lerp(0.05, 0.1, rand0_1));
        } else {
            param.velocity.x = 0;
            param.velocity.y = Random(-72.0, -36.0);
            param.deflection = Random(0.0, 400.0);
            param.color = ColorF(0.8, 0.5);
        }
        if (kind == BubbleKind::Small) {
            param.maxRadius = 1.0;
        } else if (kind == BubbleKind::Middle) {
            param.maxRadius = Random(10.0, 40.0);
        } else if (kind == BubbleKind::Big) {
            param.maxRadius = Random(60.0, 120.0);
        }

        // TODO 座標計算
        const auto& offset = pObj->getModule<Camera>()->getPos();
        static constexpr Vec2 CreateRangeOffset{ -120 - 480, 260 };
        static constexpr Vec2 CreateRangeSize{ 1080,240 };
        param.basePos = s3d::RandomVec2(RectF{ offset + CreateRangeOffset, CreateRangeSize });
        
        // メイン制御
        {
            auto main = pObj->attach<Main>(pObj);
            main->setParam(param);
        }
    }
}