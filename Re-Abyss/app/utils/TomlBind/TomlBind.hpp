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
        concept IsAutoTOMLBindable = requires(Type a)
        {
            typename Type::TOML_BIND_BEGIN_ID;
            typename Type::TOML_BIND_END_ID;
        };

        template<class Type>
        struct IsSivArray_impl : std::false_type {};

        template<class Type, class Allocator>
        struct IsSivArray_impl<s3d::Array<Type, Allocator>> : std::true_type {};

        template<class Type>
        concept IsSivArray = IsSivArray_impl<Type>::value;

        template<class Type, int Num>
        concept IsTOMLBindCallable = requires(Type a, TOMLBindId<Num> id)
        {
            { a(id) } -> std::same_as<void>;
        };

        // FIXME constevalがコンパイラ対応しだい修正
        template <IsAutoTOMLBindable Type, int Num>
        constexpr /* consteval */ int NextTOMLBindId()
        {
            if constexpr(Num == Type::TOML_BIND_END_ID::Value) {
                return Type::TOML_BIND_END_ID::Value;
            } else if constexpr (IsTOMLBindCallable<Type, Num + 1>) {
                return Num + 1;
            } else {
                return NextTOMLBindId<Type, Num + 1>();
            }
        }

        template <class Type, class Id = typename Type::TOML_BIND_BEGIN_ID>
        struct AutoTOMLBind {};

        template <IsAutoTOMLBindable Type, int Num>
        struct AutoTOMLBind<Type, TOMLBindId<Num>>
        {
            void operator()([[maybe_unused]]Type& ret, const s3d::TOMLValue& toml)
            {
                if constexpr (IsTOMLBindCallable<Type, Num>) {
                    ret(TOMLBindId<Num>{toml});
                }
                [[maybe_unused]] constexpr int nextId = NextTOMLBindId<Type, Num>();
                if constexpr (!std::is_same_v<typename Type::TOML_BIND_END_ID, TOMLBindId<nextId>>) {
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


#define TOML_BIND_BEGIN using TOML_BIND_BEGIN_ID = abyss::detail::TOMLBindId<__LINE__>
#define TOML_BIND_END using TOML_BIND_END_ID = abyss::detail::TOMLBindId<__LINE__>
#define TOML_BIND_PARAM(Value, TOMLKey)\
]] void operator()(const abyss::detail::TOMLBindId<__LINE__>& id)\
{\
    using Type = decltype(Value);\
    Value = abyss::detail::GetData<Type>(id.toml[U##TOMLKey]);\
}[[
