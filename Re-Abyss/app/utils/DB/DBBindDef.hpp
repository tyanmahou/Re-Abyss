#pragma once
#include <abyss/utils/DB/DBBind.hpp>
#include <abyss/utils/Enum/EnumTraits.hpp>
#include <abyss/utils/DateTime/DateTimeUtil.hpp>

#include <Siv3D/Duration.hpp>
#include <Siv3D/DateTime.hpp>

namespace abyss
{
	/// <summary>
	/// Duration
	/// </summary>
	template<>
	struct DBValueTraits<s3d::Duration>
	{
		s3d::Duration operator()(const s3dsql::DBValue& value) const
		{
			return s3d::Duration(value.get<double>());
		}
	};

	/// <summary>
	/// Date
	/// </summary>
	template<>
	struct DBValueTraits<s3d::Date>
	{
		s3d::Date operator()(const s3dsql::DBValue& value) const
		{
			return DateTimeUtil::ToDate(value.get<s3d::String>());
		}
	};

	/// <summary>
	/// DateTime
	/// </summary>
	template<>
	struct DBValueTraits<s3d::DateTime>
	{
		s3d::DateTime operator()(const s3dsql::DBValue& value) const
		{
			return DateTimeUtil::ToDateTime(value.get<s3d::String>());
		}
	};

	/// <summary>
	/// Enum
	/// </summary>
	template<Enum::EnumType Type>
	struct DBValueTraits<Type>
	{
		Type operator()(const s3dsql::DBValue& value) const
		{
			return Enum::Parse<Type>(value.get<s3d::String>());
		}
	};
}