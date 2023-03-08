#pragma once
#include <abyss/utils/TOML/TOMLUtil.hpp>

namespace abyss::UI::Home::Top
{
    struct ViewParam
    {
        struct IconParam
        {
            [[TOML_BIND(pos)]]
            s3d::Vec2 pos{};

            [[TOML_BIND(iconOffset)]]
            s3d::Vec2 iconOffset{};

            [[TOML_BIND(iconScale)]]
            double iconScale{1.0};

            [[TOML_BIND(text)]]
            s3d::String text{};

            [[TOML_BIND(textOffset)]]
            s3d::Vec2 textOffset{};

            [[TOML_BIND(fontSize)]]
            double fontSize{ 40.0 };

            [[TOML_BIND(scale)]]
            double scale{ 1.0 };

            [[TOML_BIND(isReverseColor)]]
            bool isReverseColor{ false };
        };

        [[TOML_BIND(ViewParam::Icons, "Icons")]]
        inline static s3d::Array<IconParam> Icons;

    };
}
