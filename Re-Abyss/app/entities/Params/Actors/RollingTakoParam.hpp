#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TomlBind/TomlBind.hpp>
namespace abyss
{
    struct RollingTakoParam
    {
        struct Base
        {
            inline static s3d::int32 Hp{ 6 };
            
            inline static s3d::Vec2 Size{ 45, 45 };

            inline static s3d::Vec2 Pivot{ 0, 7.5 };
        };

        struct Wait
        {
            inline static double SearchRange{ 300 };
        };

        struct Run
        {
            inline static double AccelX{ 180 };
            inline static double MaxSpeedX{ 200 };
        };

        inline static Base Base;

        inline static Wait Wait;

        inline static Run Run;
    };
}