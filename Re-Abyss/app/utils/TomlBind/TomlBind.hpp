#pragma once
#include <Siv3D/TOMLReader.hpp>

namespace abyss
{
    template<class Type>
    struct TomlBind
    {
        Type operator()(const s3d::TOMLValue& toml);
    };

    template<class Type>
    Type TomlBinding(const s3d::TOMLValue& toml)
    {
        return TomlBind<Type>{}(toml);
    }
}

/*

 example:

 namespace abyss
 {
     template<>
     struct TomlBind<Hoge>
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
        template<class Type>
        concept IsAutoTomlBindable = requires(Type a)
        {
            typename Type::TOML_BIND_BEGIN_ID;
            typename Type::TOML_BIND_END_ID;
        };

        template<class Type>
        struct IsSivArray : std::false_type {};

        template<class Type, class Allocator>
        struct IsSivArray<s3d::Array<Type, Allocator>> : std::true_type {};

        template<class Type>
        concept SivArrayAs = IsSivArray<Type>::value;

        template<int Num>
        struct TomlBindId
        {
            const s3d::TOMLValue& toml;
        };

        template <class T, class Id = typename T::TOML_BIND_BEGIN_ID>
        struct AutoTomlBind {};

        template <IsAutoTomlBindable T, int Num>
        struct AutoTomlBind<T, TomlBindId<Num>>
        {
            void operator()(T& ret, const s3d::TOMLValue& toml)
            {
                (ret, TomlBindId<Num>{toml});
                if constexpr (!std::is_same_v<typename T::TOML_BIND_END_ID, TomlBindId<Num + 1>>) {
                    AutoTomlBind<T, TomlBindId<Num + 1>>{}.operator()(ret, toml);
                }
            }
        };

        template <class Value>
        Value GetData(const s3d::TOMLValue& toml)
        {
            if constexpr (IsAutoTomlBindable<Value>) {
                return TomlBind<Value>{}(toml);
            } else {
                return toml.get<Value>();
            }
        }

        template <SivArrayAs Value>
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

    template<detail::IsAutoTomlBindable T>
    struct TomlBind<T>
    {
        T operator()(const s3d::TOMLValue& toml)
        {
            T ret;
            detail::AutoTomlBind<T>{}(ret, toml);
            return ret;
        }
    };


}


#define TOML_BIND_BEGIN using TOML_BIND_BEGIN_ID = abyss::detail::TomlBindId<__COUNTER__>
#define TOML_BIND_END using TOML_BIND_END_ID = abyss::detail::TomlBindId<__COUNTER__>
#define TOML_BIND_PARAM(Value, TomlKey)\
void operator, (const abyss::detail::TomlBindId<__COUNTER__>& id)\
{\
    using Type = decltype(Value);\
    Value = abyss::detail::GetData<Type>(id.toml[U##TomlKey]);\
}
