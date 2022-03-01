#pragma once
#include <abyss/utils/TomlBind/TOMLBindDef.hpp>
#include <Siv3D/Vector2D.hpp>

namespace abyss::Actor::Enemy::KingDux
{
    struct FootDesc
    {
        [[TOML_BIND(pos)]]
        s3d::Vec2 pos{ 0, 0 };
        [[TOML_BIND(animTimeOffset)]]
        double animTimeOffset = 0;
        [[TOML_BIND(rotateDeg)]]
        double rotateDeg = 0;
        [[TOML_BIND(isFlip)]]
        bool isFlip = false;
    };

    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        [[TOML_BIND(Base::EyeL, "Base.eyeL")]]
        [[TOML_BIND(Base::EyeR, "Base.eyeR")]]
        [[TOML_BIND(Base::MouthPos, "Base.mouthPos")]]
        [[TOML_BIND(Base::ColSize, "Base.colSize")]]
        [[TOML_BIND(Base::Pivot, "Base.pivot")]]
        [[TOML_BIND(Base::MainColliders, "Base.mainColliders")]]
        [[TOML_BIND(Base::CrownColliders, "Base.crownColliders")]]
        [[TOML_BIND(Base::Terrain, "Base.terrain")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 100 };
            inline static s3d::Vec2 EyeL{ 108, 155 };
            inline static s3d::Vec2 EyeR{ -117, 153 };
            inline static s3d::Vec2 MouthPos{ -20, 280 };

            inline static s3d::Vec2 ColSize{ 80, 80 };
            inline static s3d::Vec2 Pivot{ 0, 0 };

            inline static s3d::Array<s3d::Triangle> MainColliders;
            inline static s3d::Array<s3d::Triangle> CrownColliders;

            inline static s3d::RectF Terrain{};
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

        [[TOML_BIND(Foot::Foot1, "Foot.Foot1")]]
        [[TOML_BIND(Foot::Foot2, "Foot.Foot2")]]
        [[TOML_BIND(Foot::Foot3, "Foot.Foot3")]]
        [[TOML_BIND(Foot::Foot4, "Foot.Foot4")]]
        [[TOML_BIND(Foot::AnimTimeSec, "Foot.animTimeSec")]]
        [[TOML_BIND(Foot::AnimFrameMap, "Foot.animFrameMap")]]
        struct Foot
        {
            inline static FootDesc Foot1{};
            inline static FootDesc Foot2{};
            inline static FootDesc Foot3{};
            inline static FootDesc Foot4{};

            inline static double AnimTimeSec{ 1.0 };
            inline static s3d::Array<s3d::int32> AnimFrameMap{};
        };

        [[TOML_BIND(Shout::Radius, "Shout.radius")]]
        [[TOML_BIND(Shout::Power, "Shout.power")]]
        [[TOML_BIND(Shout::Time, "Shout.time")]]
        [[TOML_BIND(Shout::Count, "Shout.count")]]
        struct Shout
        {
            inline static double Radius{};
            inline static double Power{};
            inline static double Time{};
            inline static s3d::int32 Count{};
        };
    };
}