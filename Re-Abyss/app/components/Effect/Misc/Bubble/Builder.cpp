#include "Builder.hpp"
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

#include <abyss/components/Effect/Misc/Bubble/Main.hpp>
#include <abyss/components/Effect/Common/LifeTime.hpp>

#include <Siv3D.hpp>

namespace
{
    using namespace abyss;
    using namespace abyss::Effect;

    RectF BaseRect(EffectObj* pObj)
    {
        if (auto room = pObj->getModule<RoomManager>()) {
            return room->currentRoom().getRegion();
        }
        return pObj->getModule<Camera>()->screenRegion();
    }
    RectF ParallaxedRect(EffectObj* pObj, const Vec2& parallax, const s3d::Optional<s3d::RectF>& area)
    {
        auto base = area ? *area : ::BaseRect(pObj);
        auto [l, t] = base.tl();
        auto [r, b] = base.br();

        /*
          l < x < r              …① カメラの移動距離  (厳密にはScreenSize.x / 2.0小さいけど広めに計算)
          l < (p +(1 - c)x) < r  …② スクリーンないに入るか
          の不等式を整理
        */
        double cX = 1.0 - parallax.x;
        double newL = cX >= 0 ? l - cX * r : l - cX * l;
        double newR = cX >= 0 ? r - cX * l : r - cX * r;

        double cY = 1.0 - parallax.y;
        double newT = cY >= 0 ? t - cY * b : t - cY * t;
        double newB = cY >= 0 ? b - cY * t : b - cY * b;
        return RectF(newL, newT, newR - newL, newB - newT);
    }

    RectF ChoicedRect(EffectObj* pObj, const Vec2& parallax, const s3d::Optional<s3d::RectF>& area)
    {
        auto base = ::ParallaxedRect(pObj, parallax, area);
        constexpr Vec2 offset{ 0, 150 };
        constexpr double sizeY = 240.0;
        return RectF(base.bl() + offset, Vec2{ base.size.x, sizeY });
    }
}
namespace abyss::Effect::Misc::Bubble
{
    void Builder::Build(EffectObj* pObj, BubbleKind kind, LayerKind layer, const s3d::Optional<s3d::RectF>& area)
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
            param.parallax.x = param.parallax.y = 1.0;
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

        // 座標計算
        auto randArea = ::ChoicedRect(pObj, param.parallax, area);
        param.basePos = s3d::RandomVec2(randArea);
        
        // メイン制御
        {
            auto main = pObj->attach<Main>(pObj);
            main->setParam(param)
                .setArea(randArea.stretched(0, 150))
                ;
        }

        // 寿命
        {
            pObj->attach<LifeTime>(pObj)
                ->setTime(58.0, 2.0);
        }
    }
}