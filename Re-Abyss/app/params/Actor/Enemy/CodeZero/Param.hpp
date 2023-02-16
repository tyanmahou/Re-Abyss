#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOML/TOMLBind.hpp>

namespace abyss::Actor::Enemy::CodeZero
{
    struct Param
    {
        [[TOML_BIND(Base::Hp, "Base.hp")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 70 };
        };

        [[TOML_BIND(Head::ColRadius, "Head.colRadius")]]
        [[TOML_BIND(Head::Offset, "Head.offset")]]
        struct Head
        {
            inline static double ColRadius{ 35.0 };
            inline static s3d::Vec2 Offset{ 0, -50 };
        };

        [[TOML_BIND(Wing::FuwaFuwaPeriod, "Wing.fuwaFuwaPeriod")]]
        [[TOML_BIND(Wing::FuwaFuwaOffset, "Wing.fuwaFuwaOffset")]]
        [[TOML_BIND(Wing::LookOffset, "Wing.lookOffset")]]
        [[TOML_BIND(Wing::ErpRate, "Wing.erpRate")]]
        struct Wing
        {
            inline static double FuwaFuwaPeriod{ 3.0 };
            inline static s3d::Vec2 FuwaFuwaOffset{ 20, 50.0 };
            inline static s3d::Vec2 LookOffset{ 50, 50.0 };
            inline static double LookDiffRate{ 0.5 };
            inline static double ErpRate{ 0.5 };
        };

        [[TOML_BIND(Phase1::WaitRestart, "Phase1.waitRestart")]]
        [[TOML_BIND(Phase1::WaitAttack, "Phase1.waitAttack")]]
        struct Phase1
        {
            inline static double WaitRestart{ 3.0 };
            inline static double WaitAttack{ 1.2 };
        };

        [[TOML_BIND(Phase2::WaitInit, "Phase2.waitInit")]]
        [[TOML_BIND(Phase2::WaitAttack, "Phase2.waitAttack")]]
        [[TOML_BIND(Phase2::WaitDualAttack, "Phase2.waitDualAttack")]]
        [[TOML_BIND(Phase2::WaitRestart, "Phase2.waitRestart")]]
        struct Phase2
        {
            inline static double WaitInit{ 3.0 };
            inline static double WaitAttack{ 1.2 };
            inline static double WaitDualAttack{ 2.0 };
            inline static double WaitRestart{ 4.0 };
        };

        [[TOML_BIND(Phase3::WaitShot, "Phase3.waitShot")]]
        [[TOML_BIND(Phase3::WaitPursuit, "Phase3.waitPursuit")]]
        [[TOML_BIND(Phase3::WaitInitAttack, "Phase3.waitInitAttack")]]
        [[TOML_BIND(Phase3::WaitAttack, "Phase3.waitAttack")]]
        [[TOML_BIND(Phase3::WaitRestart, "Phase3.waitRestart")]]
        struct Phase3
        {
            inline static double WaitShot{ 1.0 };
            inline static double WaitPursuit{ 3.0 };
            inline static double WaitInitAttack{ 2.0 };
            inline static double WaitAttack{ 1.2 };
            inline static double WaitRestart{ 3.0 };
        };
    };
}
