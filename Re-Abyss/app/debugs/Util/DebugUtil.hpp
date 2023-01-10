#pragma once

#if ABYSS_DEBUG
#include <Siv3D/ColorF.hpp>
#include <Siv3D/String.hpp>
#include <abyss/commons/Fwd.hpp>

namespace abyss::Debug
{
    class DebugUtil
    {
    public:
        static void DrawDebug(const Actors& actors);

        static void DrawDebug(const PhysicsManager& physics);

        static void DrawShape(const CShape& shape, const s3d::ColorF& color);

        static void AlertDecorCount(const Decors& decor);
        static void AlertEffectCount(const Effects& effects);
        static void AlertDrawerCount(const DrawManager* drawManager);

        /// <summary>
        /// 対象ファイルを既定のエディタで開く
        /// </summary>
        static bool FileEdit(const s3d::FilePath& path);
    };
}

#endif
