#pragma once
#include <concepts>
#include <Siv3D/TOMLReader.hpp>
namespace abyss
{
    template<class Type>
    struct TOMLValueTraits
    {
        Type operator()(const s3d::TOMLValue& value) const
        {
            return value.get<Type>();
        }
    };

    template<class Type>
    Type GetValue(const s3d::TOMLValue& value)
    {
        return TOMLValueTraits<Type>{}(value);
    }
    template<class Type>
    s3d::Optional<Type> GetOpt(const s3d::TOMLValue& value)
    {
        if (value.isEmpty()) {
            return s3d::none;
        }
        return TOMLValueTraits<Type>{}(value);
    }

    template<class Type>
    struct TOMLValueTraits<s3d::Optional<Type>>
    {
        s3d::Optional<Type> operator()(const s3d::TOMLValue& value) const
        {
            return GetOpt<Type>(value);
        }
    };

    template<class Type>
    struct TOMLBind
    {
        // Type operator()(const s3d::TOMLValue& toml);
    };

    template<class Type>
    Type TOMLBinding(const s3d::TOMLValue& toml)
    {
        return TOMLBind<Type>{}(toml);
    }
}

/*

 example:

 namespace abyss
 {
     template<>
     struct TOMLBind<Hoge>
     {
         Hoge operator()(const s3d::TOMLValue& toml){
             // something
             return hoge;
         }
     }
 }

*/

namespace abyss
{
    namespace detail::tomlbind
    {
        inline constexpr size_t AUTO_TOML_BINDABLE_MAX_LINES = 500;
        template<size_t Num>
        struct TOMLBindId
        {
            enum : size_t
            {
                Value = Num
            };
            const s3d::TOMLValue& toml;
        };

        template<class Type>
        concept IsTOMLBindable = requires(const s3d::TOMLValue& toml)
        {
            { TOMLBind<Type>{}(toml) }->std::same_as<Type>;
        };

        template<class Type>
        struct IsSivArray_impl : std::false_type {};

        template<class Type, class Allocator>
        struct IsSivArray_impl<s3d::Array<Type, Allocator>> : std::true_type {};

        template<class Type>
        concept IsSivArray = IsSivArray_impl<Type>::value;

        template<class Type, int Num>
        concept IsTOMLBindIdCallable = requires(Type a, TOMLBindId<Num> id)
        {
            { a(id) } -> std::same_as<void>;
        };

        template <size_t... As, size_t... Bs>
        constexpr std::index_sequence<As..., Bs...> operator+(std::index_sequence<As...>, std::index_sequence<Bs...>)
        {
            return {};
        }
        template <class Type, size_t LineNum>
        constexpr auto filter_seq()
        {
            if constexpr (IsTOMLBindIdCallable<Type, LineNum>) {
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
            return make_sequence_impl<Type>(std::make_index_sequence<AUTO_TOML_BINDABLE_MAX_LINES>());
        }

        template<class Type>
        concept IsAutoTOMLBindable = decltype(make_sequence<Type>())::size() > 0;

        template<IsAutoTOMLBindable Type, size_t Num>
        void auto_bind(Type& ret, const s3d::TOMLValue& toml)
        {
            ret(TOMLBindId<Num>{toml});
        }
        template<IsAutoTOMLBindable Type, size_t ...Seq>
        void auto_bind_all_impl([[maybe_unused]] Type& ret, const s3d::TOMLValue& toml, std::index_sequence<Seq...>)
        {
            (auto_bind<Type, Seq>(ret, toml), ...);
        }
        template<IsAutoTOMLBindable Type>
        void auto_bind_all(Type& ret, const s3d::TOMLValue& toml)
        {
            auto_bind_all_impl(ret, toml, make_sequence<Type>());
        }

        template <class Value>
        Value GetData(const s3d::TOMLValue& toml)
        {
            if constexpr (IsTOMLBindable<Value>) {
                return TOMLBind<Value>{}(toml);
            } else {
                return GetValue<Value>(toml);
            }
        }

        template <IsSivArray Value>
        Value GetData(const s3d::TOMLValue& toml)
        {
            using Elm = typename Value::value_type;
            Value ret{};
            if (toml.getType() == s3d::TOMLValueType::Array) {
                for (const auto& object : toml.arrayView()) {
                    ret << GetData<Elm>(object);
                }
            } else if (toml.getType() == s3d::TOMLValueType::TableArray) {
                for (const auto& object : toml.tableArrayView()) {
                    ret << GetData<Elm>(object);
                }
            }
            return ret;
        }
    }

    template<detail::tomlbind::IsAutoTOMLBindable Type>
    struct TOMLBind<Type>
    {
        Type operator()(const s3d::TOMLValue& toml)
        {
            Type ret{};
            detail::tomlbind::auto_bind_all(ret, toml);
            return ret;
        }
    };
}

//----------------------------------------
// Macro
//----------------------------------------

#define TOML_BIND_IMPL_OVERLOAD(e1, e2, NAME, ...) NAME
#define TOML_BIND_IMPL_2(Value, TOMLKey)\
]]  void operator()(const ::abyss::detail::tomlbind::TOMLBindId<__LINE__>& id)\
{\
    static_assert(__LINE__ - 2 < ::abyss::detail::tomlbind::AUTO_TOML_BINDABLE_MAX_LINES);\
    using Type = decltype(Value);\
    Value = ::abyss::detail::tomlbind::GetData<Type>(id.toml[U##TOMLKey]);\
}[[

#define TOML_BIND_IMPL_1(Value) TOML_BIND_IMPL_2(Value, #Value)
#define TOML_BIND_PP_EXPAND( x ) x

#define TOML_BIND(...) TOML_BIND_PP_EXPAND(TOML_BIND_IMPL_OVERLOAD(__VA_ARGS__, TOML_BIND_IMPL_2, TOML_BIND_IMPL_1)(__VA_ARGS__))

