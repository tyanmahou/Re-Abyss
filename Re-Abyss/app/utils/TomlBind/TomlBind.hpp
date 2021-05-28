#pragma once
#include <concepts>
#include <Siv3D/TOMLReader.hpp>
namespace abyss
{
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
    namespace detail
    {
        inline constexpr int AUTO_TOML_BINDABLE_MAX_LINES = 500;
        template<int Num>
        struct TOMLBindId
        {
            enum
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

        template <class Type, int Num>
        consteval int NextTOMLBindId()
        {
            if constexpr (Num == AUTO_TOML_BINDABLE_MAX_LINES) {
                return AUTO_TOML_BINDABLE_MAX_LINES;
            } else if constexpr (IsTOMLBindIdCallable<Type, Num + 1>) {
                return Num + 1;
            } else {
                return NextTOMLBindId<Type, Num + 1>();
            }
        }

        template<class Type>
        concept IsAutoTOMLBindable = (NextTOMLBindId<Type, 1>() != AUTO_TOML_BINDABLE_MAX_LINES);

        template <class Type, class Id = TOMLBindId<NextTOMLBindId<Type, 1>()>>
        struct AutoTOMLBind {};

        template <IsAutoTOMLBindable Type, int Num>
        struct AutoTOMLBind<Type, TOMLBindId<Num>>
        {
            void operator()([[maybe_unused]]Type& ret, const s3d::TOMLValue& toml)
            {
                if constexpr (IsTOMLBindIdCallable<Type, Num>) {
                    ret(TOMLBindId<Num>{toml});
                }
                [[maybe_unused]] constexpr int nextId = NextTOMLBindId<Type, Num>();
                if constexpr (nextId != AUTO_TOML_BINDABLE_MAX_LINES) {
                    AutoTOMLBind<Type, TOMLBindId<nextId>>{}(ret, toml);
                }
            }
        };

        template <class Value>
        Value GetData(const s3d::TOMLValue& toml)
        {
            if constexpr (IsTOMLBindable<Value>) {
                return TOMLBind<Value>{}(toml);
            } else {
                return toml.get<Value>();
            }
        }

        template <IsSivArray Value>
        Value GetData(const s3d::TOMLValue& toml)
        {
            using Elm = typename Value::value_type;
            Value ret;
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

    template<detail::IsAutoTOMLBindable Type>
    struct TOMLBind<Type>
    {
        Type operator()(const s3d::TOMLValue& toml)
        {
            Type ret;
            detail::AutoTOMLBind<Type>{}(ret, toml);
            return ret;
        }
    };


}

//----------------------------------------
// Macro
//----------------------------------------

#define TOML_BIND_PARAM_IMPL_OVERLOAD(e1, e2, NAME, ...) NAME
#define TOML_BIND_PARAM_IMPL_2(Value, TOMLKey)\
]]  void operator()(const abyss::detail::TOMLBindId<__LINE__>& id)\
{\
    static_assert(__LINE__ - 2 < abyss::detail::AUTO_TOML_BINDABLE_MAX_LINES);\
    using Type = decltype(Value);\
    Value = abyss::detail::GetData<Type>(id.toml[U##TOMLKey]);\
}[[

#define TOML_BIND_PARAM_IMPL_1(Value) TOML_BIND_PARAM_IMPL_2(Value, #Value)
#define TOML_BIND_PP_EXPAND( x ) x

#define TOML_BIND_PARAM(...) TOML_BIND_PP_EXPAND(TOML_BIND_PARAM_IMPL_OVERLOAD(__VA_ARGS__, TOML_BIND_PARAM_IMPL_2, TOML_BIND_PARAM_IMPL_1)(__VA_ARGS__))

