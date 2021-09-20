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
        [[TOML_BIND(Base::ColSize, "Base.colSize")]]
        [[TOML_BIND(Base::Pivot, "Base.pivot")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 100 };
            inline static s3d::Vec2 EyeL{ 108, 155 };
            inline static s3d::Vec2 EyeR{ -117, 153 };
            inline static s3d::Vec2 MouthPos{ -20, 280 };

            inline static s3d::Vec2 ColSize{ 80, 80 };
            inline static s3d::Vec2 Pivot{ 0, 0 };
        };

        [[TOML_BIND(Eye::DistRate, "Eye.distRate")]]
        [[TOML_BIND(Eye::ErpRate, "Eye.erpRate")]]
        [[TOML_BIND(Eye::DamageErpRate, "Eye.damageErpRate")]]
        [[TOML_BIND(Eye::LimitBeginL, "Eye.limitBeginL")]]
        [[TOML_BIND(Eye::LimitEndL, "Eye.limitEndL")]]
        [[TOML_BIND(Eye::LimitBeginR, "Eye.limitBeginR")]]
        [[TOML_BIND(Eye::LimitEndR, "Eye.limitEndR")]]
        struct Eye
        {
            inline static double DistRate{ 0.005 };
            inline static double ErpRate{ 0.02 };
            inline static double DamageErpRate{ 0.5 };

            inline static s3d::Vec2 LimitBeginL{ 108, 155 };
            inline static s3d::Vec2 LimitEndL{ 108, 155 };
            inline static s3d::Vec2 LimitBeginR{ 108, 155 };
            inline static s3d::Vec2 LimitEndR{ 108, 155 };
        };

        [[TOML_BIND(Foot::PosL, "Foot.posL")]]
        [[TOML_BIND(Foot::PosR, "Foot.posR")]]
        [[TOML_BIND(Foot::AnimTimeSec, "Foot.animTimeSec")]]
        [[TOML_BIND(Foot::AnimFrameMap, "Foot.animFrameMap")]]
        struct Foot
        {
            inline static s3d::Vec2 PosL{ 100, 310 };
            inline static s3d::Vec2 PosR{ -500, 310 };

            inline static double AnimTimeSec{ 1.0 };
            inline static s3d::Array<s3d::int32> AnimFrameMap{};
        };
    };
}