#pragma once
#include <Siv3DSQL.hpp>

namespace abyss
{
    template<class Type>
	struct DBValueTraits
	{
		Type operator()(const s3dsql::DBValue& value) const
		{
			return value.get<Type>();
		}
	};

	template<class Type>
	Type GetValue(const s3dsql::DBValue& value)
	{
		return DBValueTraits<Type>{}(value);
	}
	template<class Type>
	s3d::Optional<Type> GetOpt(const s3dsql::DBValue& value)
	{
		if (value.isNull()) {
			return s3d::none;
		}
		return DBValueTraits<Type>{}(value);
	}

	template<class Type>
	struct DBBind
	{
		// Type operator()(s3dsql::DBRow& row) const;
	};

	template<class Type>
	concept DBBindable = requires(s3dsql::DBRow & row)
	{
		{ DBBind<Type>{}(row) }->std::same_as<Type>;
	};

	template<DBBindable Type>
	Type FromRow(s3dsql::DBRow& row)
	{
		return DBBind<Type>{}(row);
	}
}