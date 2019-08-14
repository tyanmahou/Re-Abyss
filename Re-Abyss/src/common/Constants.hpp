#pragma once
#include <Siv3D/Rectangle.hpp>
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/Color.hpp>

namespace abyss
{
	namespace Constants
	{
		// Application
		constexpr s3d::Size WindowSize{ 960, 540 };
		constexpr s3d::Size GameScreenSize{ 960, 520 };
		constexpr s3d::Vec2 GameScreenOffset{ 0, 20 };


		// Game
		namespace Player {
			constexpr double MaxGravity = 1.3;
			constexpr double DiveSpeed = 2.2;
			constexpr double MaxSpeed = 4;

			constexpr s3d::int32 SmallCharge = 10;
			constexpr s3d::int32 MediumCharge = 60;
			constexpr s3d::Color MediumChargeColorBase{ 128, 128, 255 };
			constexpr s3d::int32 BigCharge = 120;
			constexpr s3d::Color BigChargeColorBase{255, 255, 0};
		}
	}
}