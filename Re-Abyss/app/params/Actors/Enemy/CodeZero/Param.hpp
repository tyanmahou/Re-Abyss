#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss::CodeZero
{
    struct Param
    {
        [[TOML_BIND_PARAM(Base::Hp, "Base.hp")]]
        struct Base
        {
            inline static s3d::int32 Hp{ 70 };
        };

        [[TOML_BIND_PARAM(Head::ColRadius, "Head.colRadius")]]
        [[TOML_BIND_PARAM(Head::Offset, "Head.offset")]]
        struct Head
        {
            inline static double ColRadius{ 35.0 };
            inline static s3d::Vec2 Offset{ 0, -50 };
        };

        [[TOML_BIND_PARAM(Phase1::WaitRestart, "Phase1.waitRestart")]]
        [[TOML_BIND_PARAM(Phase1::WaitAttack, "Phase1.waitAttack")]]
        struct Phase1
        {
            inline static double WaitRestart{ 3.0 };
            inline static double WaitAttack{ 1.2 };
        };

        [[TOML_BIND_PARAM(Phase2::WaitInit, "Phase2.waitInit")]]
        [[TOML_BIND_PARAM(Phase2::WaitAttack, "Phase2.waitAttack")]]
        [[TOML_BIND_PARAM(Phase2::WaitDualAttack, "Phase2.waitDualAttack")]]
        [[TOML_BIND_PARAM(Phase2::WaitRestart, "Phase2.waitRestart")]]
        struct Phase2
        {
            inline static double WaitInit{ 3.0 };
            inline static double WaitAttack{ 1.2 };
            inline static double WaitDualAttack{ 2.0 };
            inline static double WaitRestart{ 4.0 };
        };

        [[TOML_BIND_PARAM(Phase3::WaitShot, "Phase3.waitShot")]]
        [[TOML_BIND_PARAM(Phase3::WaitPursuit, "Phase3.waitPursuit")]]
        [[TOML_BIND_PARAM(Phase3::WaitInitAttack, "Phase3.waitInitAttack")]]
        [[TOML_BIND_PARAM(Phase3::WaitAttack, "Phase3.waitAttack")]]
        [[TOML_BIND_PARAM(Phase3::WaitRestart, "Phase3.waitRestart")]]
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