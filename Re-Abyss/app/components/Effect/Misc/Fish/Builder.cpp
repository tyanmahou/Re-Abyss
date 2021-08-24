#include "Builder.hpp"
#include <abyss/commons/Constants.hpp>
#include <abyss/modules/Effect/base/EffectObj.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>

#include <abyss/components/Effect/Misc/Fish/Main.hpp>
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
        return base.stretched(Constants::GameScreenSize.x / 2.0, 0.0);
    }
}
namespace abyss::Effect::Misc::Fish
{
    void Builder::Build(EffectObj* pObj, LayerKind layer, const s3d::Optional<s3d::RectF>& area)
    {
        // メイン制御
        auto main = pObj->attach<Main>(pObj, Random(0, 21));

        double rand0_1 = Random();
        // パララックス係数
        // スケール
        // カラー
        Vec2 parallax{ 1.0, 1.0 };
        double scale = 1.0;
        double alpha = 1.0;
        if (layer == LayerKind::Back) {
            parallax.x = parallax.y = Math::Lerp(0.6, 0.95, rand0_1);
            scale = s3d::Math::Lerp(0.4, 1.0, rand0_1);
            alpha = s3d::Math::Lerp(0.02, 0.1, rand0_1);
        } else {
            parallax.x = parallax.y = Math::Lerp(1.05, 1.4, rand0_1);
            scale = s3d::Math::Lerp(1.0, 1.6, rand0_1);
            alpha = s3d::Math::Lerp(0.1, 0.3, rand0_1);
        }
        main->setParallax(parallax);        
        main->setScale(scale);
        main->setColor(ColorF(0.4, alpha));
        // 座標計算
        Vec2 basePos{};
        auto randArea = ::ChoicedRect(pObj, parallax, area);
        auto screen = pObj->getModule<Camera>()->screenRegion();
        do {
            basePos = s3d::RandomVec2(randArea);
            main->setBasePos(basePos);
        } while (main->isInArea(screen));

        {
            Vec2 velocity{};
            velocity.x = Random(100.0, 50.0) * (screen.center().x - basePos.x > 0 ? 1.0 : -1.0);
            velocity.y = Random(-30.0, 30.0);
            main->setVelocity(velocity);
        }

        // 寿命
        {
            pObj->attach<LifeTime>(pObj)
                ->setTime(58.0, 2.0);
        }
    }
}