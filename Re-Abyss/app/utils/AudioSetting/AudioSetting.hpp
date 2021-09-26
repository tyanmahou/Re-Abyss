#pragma once
#include <variant>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>
namespace abyss
{
    struct AudioSetting
    {
        s3d::String path;
        std::variant<s3d::Loop, s3d::Duration, s3d::Vector2D<s3d::Duration>> loop = s3d::Loop::No;

        /// <summary>
        /// ロード
        /// </summary>
        /// <returns></returns>
        s3d::Audio load() const;

        /// <summary>
        /// Waveに設定を適用する
        /// </summary>
        /// <param name="wave"></param>
        /// <returns></returns>
        s3d::Audio apply(const s3d::Wave& wave) const;
    };

}