#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>

namespace abyss
{
	/// <summary>
	/// Duration
	/// </summary>
	template<>
	struct TOMLValueTraits<s3d::Duration>
	{
		s3d::Duration operator()(const s3d::TOMLValue& value) const
		{
			return s3d::Duration(value.get<double>());
		}
	};
}