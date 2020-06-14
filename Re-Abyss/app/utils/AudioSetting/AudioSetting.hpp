#pragma once
#include <variant>
#include <Siv3D/String.hpp>
#include <Siv3D/Vector2D.hpp>
namespace abyss
{
    struct AudioSetting
    {
        s3d::String path;
        std::variant<s3d::None_t, bool, s3d::Vec2> loop = s3d::none;

        /// <summary>
        /// 設定を適用する
        /// </summary>
        /// <param name="audio"></param>
        void apply(s3d::Audio& audio);
    };

}