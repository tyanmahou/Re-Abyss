#pragma once
#include <Siv3DSQL.hpp>

namespace abyss
{
    template<class Type>
	struct DBBind
	{
		Type operator()(const s3dsql::DBValue& row) const
		{
			return row.get<Type>();
		}
	};

	template<class Type>
	Type FromRow(const s3dsql::DBValue& row)
	{
		return DBBind<Type>{}(row);
	}
	template<class Type>
	s3d::Optional<Type> FromRowOpt(const s3dsql::DBValue& row)
	{
		if (row.isNull()) {
			return s3d::none;
		}
		return DBBind<Type>{}(row);
	}
}