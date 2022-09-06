#pragma once
#include <Siv3D/RectF.hpp>

namespace abyss::Actor::Gimmick::ShutterWall
{
    class ShutterUtil
    {
    public:
        /// <summary>
        /// あたり範囲
        /// </summary>
        /// <param name="pos">左上座標</param>
        /// <param name="shutterRate">開閉レート</param>
        /// <returns></returns>
        static s3d::RectF Region(const s3d::Vec2& pos, double shutterRate = 1.0);
    };
}
