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
		inline constexpr size_t AUTO_DB_BIND_MAX_LINES = 500;

		template<size_t Line>
		struct AutoDBBindLine
		{
			s3dsql::DBRow& row;
		};

		template<class Type, size_t LineNum>
		concept AutoDBBindCallable = requires(Type t, AutoDBBindLine<LineNum> l)
		{
			t | l;
		};

		namespace DBBind
		{
			template <size_t... As, size_t... Bs>
			constexpr std::index_sequence<As..., Bs...> operator+(std::index_sequence<As...>, std::index_sequence<Bs...>)
			{
				return {};
			}
			template <class Type, size_t LineNum>
			constexpr auto filter_seq()
			{
				if constexpr (AutoDBBindCallable<Type, LineNum>) {
					return std::index_sequence<LineNum>{};
				} else {
					return std::index_sequence<>{};
				}
			}
			template <class Type, size_t ...Seq>
			constexpr auto make_sequence_impl(std::index_sequence<Seq...>)
			{
				return (filter_seq<Type, Seq>() + ...);
			}

			template <class Type>
			constexpr auto make_sequence()
			{
				return make_sequence_impl<Type>(std::make_index_sequence<AUTO_DB_BIND_MAX_LINES>());
			}
		}

		template<class Type>
		concept AutoDBBindable = decltype(DBBind::make_sequence<Type>())::size() > 0;

		template<AutoDBBindable Type, size_t LineNum>
		void auto_inject([[maybe_unused]] Type& ret, s3dsql::DBRow& row)
		{
			ret | AutoDBBindLine<LineNum>{row};
		}
		template<AutoDBBindable Type, size_t ...Seq>
		void auto_inject_all([[maybe_unused]] Type& ret, s3dsql::DBRow& row, std::index_sequence<Seq...>)
		{
			(auto_inject<Type, Seq>(ret, row), ...);
		}
	}
	template<detail::AutoDBBindable Type>
	struct DBBind<Type>
	{
		Type operator()(s3dsql::DBRow& row) const
		{
			Type ret{};
			detail::auto_inject_all(ret, row, detail::DBBind::make_sequence<Type>());
			return ret;
		}
	};
}

//----------------------------------------
// Macro
//----------------------------------------
#define DB_BIND_PP_IMPL_OVERLOAD_2(e1, e2, NAME, ...) NAME
#define DB_BIND_PP_IMPL_OVERLOAD_3(e1, e2, e3, NAME, ...) NAME
#define DB_BIND_PP_EXPAND( x ) x

// DB_COLUMN
#define DB_COLUMN_IMPL_2(value, columnName) ]]\
void operator|(const ::abyss::detail::AutoDBBindLine<__LINE__>& l){\
    static_assert(__LINE__ < ::abyss::detail::AUTO_DB_BIND_MAX_LINES);\
    value = ::abyss::GetValue<decltype(value)>(l.row[U##columnName]);\
}[[
#define DB_COLUMN_IMPL_1(value) DB_COLUMN_IMPL_2(value, #value)
#define DB_COLUMN(...) DB_BIND_PP_EXPAND(DB_BIND_PP_IMPL_OVERLOAD_2(__VA_ARGS__, DB_COLUMN_IMPL_2, DB_COLUMN_IMPL_1)(__VA_ARGS__))

// DB_COLUMN_OPT
#define DB_COLUMN_OPT_IMPL_3(value, columnName, optValue) ]]\
void operator|(const ::abyss::detail::AutoDBBindLine<__LINE__>& l){\
    static_assert(__LINE__ < ::abyss::detail::AUTO_DB_BIND_MAX_LINES);\
    value = ::abyss::GetOpt<decltype(value)>(l.row[U##columnName]).value_or(optValue);\
}[[
#define DB_COLUMN_OPT_IMPL_2(value, columnName) DB_COLUMN_OPT_IMPL_3(value, columnName, decltype(value){})
#define DB_COLUMN_OPT_IMPL_1(value) DB_COLUMN_OPT_IMPL_2(value, #value)
#define DB_COLUMN_OPT(...) DB_BIND_PP_EXPAND(DB_BIND_PP_IMPL_OVERLOAD_3(__VA_ARGS__, DB_COLUMN_OPT_IMPL_3, DB_COLUMN_OPT_IMPL_2, DB_COLUMN_OPT_IMPL_1)(__VA_ARGS__))
