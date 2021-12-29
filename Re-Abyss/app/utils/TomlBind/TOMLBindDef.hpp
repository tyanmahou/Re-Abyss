#pragma once
#include <abyss/utils/TOMLBind/TOMLBind.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>

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

	/// <summary>
	/// Enum
	/// </summary>
	template<Enum::EnumType Type>
	struct TOMLValueTraits<Type>
	{
		Type operator()(const s3d::TOMLValue& value) const
		{
			return Enum::Parse<Type>(value.get<s3d::String>());
		}
	};
}