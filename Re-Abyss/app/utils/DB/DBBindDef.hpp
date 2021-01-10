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
	struct DBBind<s3d::Duration>
	{
		s3d::Duration operator()(const s3dsql::DBValue& row) const
		{
			return s3d::Duration(row.get<double>());
		}
	};

	/// <summary>
	/// Date
	/// </summary>
	template<>
	struct DBBind<s3d::Date>
	{
		s3d::Date operator()(const s3dsql::DBValue& row) const
		{
			return DateTimeUtil::ToDate(row.get<s3d::String>());
		}
	};

	/// <summary>
	/// DateTime
	/// </summary>
	template<>
	struct DBBind<s3d::DateTime>
	{
		s3d::DateTime operator()(const s3dsql::DBValue& row) const
		{
			return DateTimeUtil::ToDateTime(row.get<s3d::String>());
		}
	};

	/// <summary>
	/// Enum
	/// </summary>
	template<EnumTraity Type>
	struct DBBind<Type>
	{
		Type operator()(const s3dsql::DBValue& row) const
		{
			return Parse<Type>(row.get<s3d::String>());
		}
	};
}