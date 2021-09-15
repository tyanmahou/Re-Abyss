#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::EyeL, "Base.eyeL")]]
        [[TOML_BIND(Base::EyeR, "Base.eyeR")]]
        [[TOML_BIND(Base::MouthPos, "Base.mouthPos")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 100 };
            inline static s3d::Vec2 EyeL{ 108, 155 };
            inline static s3d::Vec2 EyeR{ -117, 153 };
            inline static s3d::Vec2 MouthPos{ -20, 280 };
        };

        [[TOML_BIND(Eye::DistRate, "Eye.distRate")]]
        [[TOML_BIND(Eye::ErpRate, "Eye.erpRate")]]
        struct Eye
        {
            inline static double DistRate{ 0.005 };
            inline static double ErpRate{ 0.3 };
        };
    };
}