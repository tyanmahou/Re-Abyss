#pragma once
#include <Siv3D/Vector2D.hpp>
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss
{
    struct CodeZeroParam
    {
        TOML_BIND_BEGIN;

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

        [[TOML_BIND_PARAM(Hand::ColRadius, "Hand.colRadius")]]
        [[TOML_BIND_PARAM(Hand::PursuitSpeed, "Hand.pursuitSpeed")]]
        [[TOML_BIND_PARAM(Hand::SetUpSpeed, "Hand.setUpSpeed")]]
        [[TOML_BIND_PARAM(Hand::AttackSpeed, "Hand.attackSpeed")]]
        [[TOML_BIND_PARAM(Hand::AttackWaitTimeSec, "Hand.attackWaitTimeSec")]]
        struct Hand
        {
            inline static double ColRadius{ 35.0 };
            inline static double PursuitSpeed{ 300.0 };
            inline static double SetUpSpeed{ 180.0 };
            inline static double AttackSpeed{ 800.0 };
            inline static double AttackWaitTimeSec{ 0.5 };
        };

        [[TOML_BIND_PARAM(Attack::IntervalTimeSec, "Attack.intervalTimeSec")]]
        struct Attack
        {
            inline static double IntervalTimeSec{ 0.5 };
        };
        TOML_BIND_END;
    };
}