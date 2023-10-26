#pragma once
#include <abyss/utils/TOML/TOMLBind.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::BossArrival
{
    struct Param
    {
        [[TOML_BIND(FontSize, "fontSize")]]
        inline static s3d::int32 FontSize{40};

        [[TOML_BIND(Pivot0, "pivot0")]]
        inline static double Pivot0{ 90 };

        [[TOML_BIND(Pivot1, "pivot1")]]
        inline static double Pivot1{ 150 };
    };
}
