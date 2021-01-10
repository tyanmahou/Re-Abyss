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
	struct DBValueTraits<s3d::Optional<Type>>
	{
		s3d::Optional<Type> operator()(const s3dsql::DBValue& value) const
		{
			return GetOpt<Type>(value);
		}
	};

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

	//----------------------------------------
	// Auto Bind
	//----------------------------------------
	namespace detail
	{
		inline constexpr int AUTO_DB_BIND_MAX_LINES = 500;

		template<int Line>
		struct AutoDBBindLine
		{
			s3dsql::DBRow& row;
		};

		template<class Type, int LineNum>
		concept AutoDBBindCallable = requires(Type t, AutoDBBindLine<LineNum> l)
		{
			t | l;
		};

		template <class Type, int LineNum>
		consteval int NextAutoDBBindLine()
		{
			if constexpr (LineNum == AUTO_DB_BIND_MAX_LINES) {
				return AUTO_DB_BIND_MAX_LINES;
			} else if constexpr (AutoDBBindCallable<Type, LineNum + 1>) {
				return LineNum + 1;
			} else {
				return NextAutoDBBindLine<Type, LineNum + 1>();
			}
		}
		template<class Type>
		concept AutoDBBindable = (NextAutoDBBindLine<Type, 1>() != AUTO_DB_BIND_MAX_LINES);

		template <class Type, int LineNum = NextAutoDBBindLine<Type, 1>()>
		struct AutoDBBinder {};

		template <AutoDBBindable Type, int LineNum>
		struct AutoDBBinder<Type, LineNum>
		{
			void operator()([[maybe_unused]] Type& ret, s3dsql::DBRow& row)
			{
				if constexpr (AutoDBBindCallable<Type, LineNum>) {
					ret | AutoDBBindLine<LineNum>{row};
				}
				[[maybe_unused]] constexpr int nextId = NextAutoDBBindLine<Type, LineNum>();
				if constexpr (nextId != AUTO_DB_BIND_MAX_LINES) {
					AutoDBBinder<Type, nextId>{}(ret, row);
				}
			}
		};
	}
	template<detail::AutoDBBindable Type>
	struct DBBind<Type>
	{
		Type operator()(s3dsql::DBRow& row) const
		{
			Type ret;
			detail::AutoDBBinder<Type>{}(ret, row);
			return ret;
		}
	};
}

//----------------------------------------
// Macro
//----------------------------------------
#define DB_BIND_PP_IMPL_OVERLOAD_2(e1, e2, NAME, ...) NAME
#define DB_BIND_PP_IMPL_OVERLOAD_3(e1, e2, e3, NAME, ...) NAME
#define DB_BIND_PP_EXPAND(x) x

// DB_COLUMN
#define DB_COLUMN_IMPL_2(value, columnName) ]];\
template<class ThisType>\
friend auto operator|(ThisType& a, const ::abyss::detail::AutoDBBindLine<__LINE__>& l){\
    static_assert(__LINE__ < ::abyss::detail::AUTO_DB_BIND_MAX_LINES);\
    a.value = ::abyss::GetValue<decltype(a.value)>(l.row[U##columnName]);\
}[[
#define DB_COLUMN_IMPL_1(value) DB_COLUMN_PP_IMPL_2(value, #value)
#define DB_COLUMN(...) DB_BIND_PP_EXPAND(DB_BIND_PP_IMPL_OVERLOAD_2(__VA_ARGS__, DB_COLUMN_IMPL_2, DB_COLUMN_IMPL_1)(__VA_ARGS__))

// DB_COLUMN_OPT
#define DB_COLUMN_OPT_IMPL_3(value, columnName, optValue) ]];\
template<class ThisType>\
friend auto operator|(ThisType& a, const ::abyss::detail::AutoDBBindLine<__LINE__>& l){\
    static_assert(__LINE__ < ::abyss::detail::AUTO_DB_BIND_MAX_LINES);\
    a.value = ::abyss::GetOpt<decltype(a.value)>(l.row[U##columnName]).value_or(optValue);\
}[[
#define DB_COLUMN_OPT_IMPL_2(value, columnName) DB_COLUMN_OPT_IMPL_3(value, columnName, {})
#define DB_COLUMN_OPT_IMPL_1(value) DB_COLUMN_OPT_IMPL_2(value, #value)
#define DB_COLUMN_OPT(...) DB_BIND_PP_EXPAND(DB_BIND_PP_IMPL_OVERLOAD_3(__VA_ARGS__, DB_COLUMN_OPT_IMPL_3, DB_COLUMN_OPT_IMPL_2, DB_COLUMN_OPT_IMPL_1)(__VA_ARGS__))
