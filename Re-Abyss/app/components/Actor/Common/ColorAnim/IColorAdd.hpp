#pragma once
#include <Siv3D/ColorF.hpp>

namespace abyss::Actor::ColorAnim
{
	/// <summary>
	/// 加算色アニメインターフェース
	/// </summary>
	class IColorAdd
	{
	public:
		virtual ~IColorAdd() = default;
		virtual size_t indexMaskAdd() const
		{
			return 1;
		}
		virtual s3d::ColorF colorAdd() const = 0;
	};
}