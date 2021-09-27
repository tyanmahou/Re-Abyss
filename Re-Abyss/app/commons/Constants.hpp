#pragma once
#include <Siv3D/Vector2D.hpp>
#include <Siv3D/RectF.hpp>
#include <Siv3D/Types.hpp>

/// <summary>
/// 定数
/// </summary>
namespace abyss::Constants
{
    // アプリ名
    inline constexpr auto* const AppName = U"Abyss Dream";
    // 解像度
    template<class Type>
    inline constexpr s3d::Vector2D<Type> AppResolution_v{ 1120, 630 };
    inline constexpr s3d::Size AppResolution = AppResolution_v<s3d::int32>.asPoint();
    inline constexpr s3d::Vec2 AppResolutionF = AppResolution_v<double>;

	template<class Type>
	inline constexpr s3d::Vector2D<Type> GameScreenSize_v{1120, 640};
	template<class Type>
	inline constexpr s3d::Vector2D<Type> GameScreenOffset_v{0, -10};

    inline constexpr s3d::Vec2 GameScreenSize = GameScreenSize_v<double>;
    inline constexpr s3d::Vec2 GameScreenOffset = GameScreenOffset_v<double>;

    inline constexpr s3d::RectF GameScreen{ GameScreenOffset , GameScreenSize };

    // セーブデータの個数
    inline constexpr s3d::int32 UserNum = 9;
}