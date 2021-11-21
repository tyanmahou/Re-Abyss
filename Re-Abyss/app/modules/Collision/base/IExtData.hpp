#pragma once
#include <any>

namespace abyss::Collision
{
	/// <summary>
	/// 拡張データ
	/// </summary>
	class IExtData
	{
	public:
		virtual ~IExtData() = default;
		virtual std::any data() const = 0;
	};
}