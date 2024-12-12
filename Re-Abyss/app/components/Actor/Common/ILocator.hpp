#pragma once
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor
{
    class ILocator
    {
    public:
        virtual ~ILocator() = default;

        /// <summary>
        /// アンカー座標
        /// </summary>
        /// <returns></returns>
        virtual s3d::Vec2 getAnchoredPos() const = 0;

        /// <summary>
        /// 中央座標
        /// </summary>
        /// <returns></returns>
        virtual s3d::Vec2 getCenterPos() const = 0;
    };
}
