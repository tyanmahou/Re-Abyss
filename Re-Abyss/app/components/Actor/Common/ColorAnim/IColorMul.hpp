#pragma once
#include <Siv3D/ColorF.hpp>

namespace abyss::Actor::ColorAnim
{
	/// <summary>
	/// 乗算カラーアニメインターフェース
	/// </summary>
	class IColorMul
	{
	public:
		virtual ~IColorMul() = default;
		virtual size_t indexMaskMul() const 
		{
			return 1;
		}
		virtual s3d::ColorF colorMul() const = 0;
	};
}