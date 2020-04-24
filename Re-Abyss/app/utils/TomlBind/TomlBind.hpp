#pragma once
#include <concepts>
#include <Siv3D/TOMLReader.hpp>
namespace abyss
{
    template<class Type>
    struct TOMLBind
    {
        Type operator()(const s3d::TOMLValue& toml);
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
            const s3d::TOMLValue& toml;
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
            { (a, id) } -> std::same_as<void>;
        };


        template <class T, class Id = typename T::TOML_BIND_BEGIN_ID>
        struct AutoTOMLBind {};

        template <IsAutoTOMLBindable T, int Num>
        struct AutoTOMLBind<T, TOMLBindId<Num>>
        {
            void operator()([[maybe_unused]]T& ret, const s3d::TOMLValue& toml)
            {
                if constexpr (IsTOMLBindCallable<T, Num>) {
                    (ret, TOMLBindId<Num>{toml});
                }
                if constexpr (!std::is_same_v<typename T::TOML_BIND_END_ID, TOMLBindId<Num + 1>>) {
                    AutoTOMLBind<T, TOMLBindId<Num + 1>>{}.operator()(ret, toml);
                }
            }
        };

        template <class Value>
        Value GetData(const s3d::TOMLValue& toml)
        {
            if constexpr (IsAutoTOMLBindable<Value>) {
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

    template<detail::IsAutoTOMLBindable T>
    struct TOMLBind<T>
    {
        T operator()(const s3d::TOMLValue& toml)
        {
            T ret;
            detail::AutoTOMLBind<T>{}(ret, toml);
            return ret;
        }
    };


}


#define TOML_BIND_BEGIN using TOML_BIND_BEGIN_ID = abyss::detail::TOMLBindId<__COUNTER__>
#define TOML_BIND_END using TOML_BIND_END_ID = abyss::detail::TOMLBindId<__COUNTER__>
#define TOML_BIND_PARAM(Value, TOMLKey)\
]] void operator, (const abyss::detail::TOMLBindId<__COUNTER__>& id)\
{\
    using Type = decltype(Value);\
    Value = abyss::detail::GetData<Type>(id.toml[U##TOMLKey]);\
}[[
