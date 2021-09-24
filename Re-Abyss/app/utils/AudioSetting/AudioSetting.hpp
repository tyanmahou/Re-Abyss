#pragma once
#include <variant>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>
namespace abyss
{
    struct AudioSetting
    {
        s3d::String path;
        std::variant<bool, s3d::Duration, s3d::Vector2D<s3d::Duration>> loop = false;

        /// <summary>
        /// 設定を適用する
        /// </summary>
        /// <param name="audio"></param>
        void apply(s3d::Audio& audio);
    };

}