#pragma once
#include <Siv3D/Vector2D.hpp>

/// <summary>
/// 定数
/// </summary>
namespace abyss::Constants
{
    // アプリ名
    inline constexpr auto* const AppName = U"Abyss Dream";
    // 解像度
    inline constexpr s3d::Size AppResolution{ 960, 540 };

    inline constexpr s3d::Vec2 GameScreenSize{ 960, 520 };
    inline constexpr s3d::Vec2 GameScreenOffset{ 0, 20 };

	// Game
	// TODO: 外部ファイルに出したい
	namespace Player
	{
		inline constexpr double MaxGravity = 1.3;
		inline constexpr double DiveSpeed = 2.2;
		inline constexpr double MaxSpeed = 4;

		inline constexpr s3d::int32 SmallCharge = 10;
		inline constexpr s3d::int32 MediumCharge = 60;
		inline constexpr s3d::Color MediumChargeColorBase{ 128, 128, 255 };
		inline constexpr s3d::int32 BigCharge = 120;
		inline constexpr s3d::Color BigChargeColorBase{ 255, 255, 0 };
	}
}