#pragma once
#include <variant>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss
{
    struct AudioSetting
    {
        s3d::FilePath path;
        std::variant<s3d::Loop, s3d::Duration, s3d::Vector2D<s3d::Duration>> loop = s3d::Loop::No;
        s3d::uint64 samplingRate = 0;
        bool streaming = false;

        /// <summary>
        /// ロード
        /// </summary>
        /// <returns></returns>
        s3d::Audio load() const;

        /// <summary>
        /// ロード
        /// </summary>
        /// <returns></returns>
        s3d::Audio loadWave() const;

        /// <summary>
        /// ストリーミングロード
        /// </summary>
        /// <returns></returns>
        s3d::Audio loadStreamimg() const;

        /// <summary>
        /// ストリーミングロード
        /// </summary>
        /// <returns></returns>
        s3d::Audio loadStreamimg(s3d::FilePathView otherPath) const;

        /// <summary>
        /// Waveに設定を適用する
        /// </summary>
        /// <param name="wave"></param>
        /// <returns></returns>
        s3d::Audio apply(const s3d::Wave& wave) const;
    };

}
