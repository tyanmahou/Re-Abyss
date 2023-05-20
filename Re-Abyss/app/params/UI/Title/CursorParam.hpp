#pragma once
#include <abyss/utils/TOML/TOMLBindDef.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::UI::Title
{
    struct CursorParam
    {
        [[TOML_BIND(ViewParam::PosX, "ViewParam.posX")]]
        [[TOML_BIND(ViewParam::PosY_GameStart, "ViewParam.posY_GameStart")]]
        [[TOML_BIND(ViewParam::PosY_Exit, "ViewParam.posY_Exit")]]
        [[TOML_BIND(ViewParam::ShotOffset, "ViewParam.shotOffset")]]
        struct ViewParam
        {
            inline static double PosX{ -130.0 };
            inline static double PosY_GameStart{ 90.0 };
            inline static double PosY_Exit{ 140.0 };
            inline static s3d::Vec2 ShotOffset{ 30, -1 };

            static s3d::Vec2 Pos(size_t mode)
            {
                return { PosX , PosY(mode)};
            }
            static double PosY(size_t mode)
            {
                if (mode == 0) {
                    return PosY_GameStart;
                } else {
                    return PosY_Exit;
                }
            }
        };
    };
}
