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
    template<class Type>
    inline constexpr s3d::Vector2D<Type> AppResolution_v{ 960, 540 };
    inline constexpr s3d::Size AppResolution = AppResolution_v<s3d::int32>.asPoint();
    inline constexpr s3d::Vec2 AppResolutionF = AppResolution_v<double>;

	template<class Type>
	inline constexpr s3d::Vector2D<Type> GameScreenSize_v{960, 520};
	template<class Type>
	inline constexpr s3d::Vector2D<Type> GameScreenOffset_v{0, 20};

    inline constexpr s3d::Vec2 GameScreenSize = GameScreenSize_v<double>;
    inline constexpr s3d::Vec2 GameScreenOffset = GameScreenOffset_v<double>;
}