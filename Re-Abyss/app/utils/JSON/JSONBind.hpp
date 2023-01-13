#pragma once
#include <concepts>
#include <Siv3D/JSON.hpp>

namespace abyss
{
    namespace detail::jsonbind {
        template<class Type>
        Type Get(const s3d::JSON& value);
    }

    template<class Type>
    struct JSONValueTraits
    {
        Type fromJSON(const s3d::JSON& value) const
        {
            return value.get<Type>();
        }
    };
    template<class Type>
    struct JSONValueTraits<s3d::Optional<Type>>
    {
        s3d::Optional<Type> fromJSON(const s3d::JSON& value) const
        {
            if (value.isNull() || value.isEmpty()) {
                return s3d::none;
            }
            return detail::jsonbind::Get<Type>(value);
        }
    };

    template<class Type, class Allocator>
    struct JSONValueTraits<s3d::Array<Type, Allocator>>
    {
        s3d::Array<Type, Allocator> fromJSON(const s3d::JSON& value) const
        {
            s3d::Array<Type, Allocator> ret{};
            if (value.isArray()) {
                for (const auto& object : value.arrayView()) {
                    ret << detail::jsonbind::Get<Type>(object);
                }
            }
            return ret;
        }
    };

    template<class Type>
    struct JSONBind
    {
        // Type fromJSON(const s3d::JSON& value) const
    };

    namespace detail::jsonbind
    {
        inline constexpr size_t AUTO_JSON_BINDABLE_MAX_LINES = 500;

        template<size_t Num>
        struct JSONBindId
        {
            enum : size_t
            {
                Value = Num
            };
            const s3d::JSON& json;
        };


        template<class Type>
        concept IsJSONBindable = requires(const s3d::JSON & json)
        {
            { JSONBind<Type>{}.fromJSON(json) }->std::same_as<Type>;
        };

        template<class Type, int Num>
        concept IsJSONBindIdCallable = requires(Type a, JSONBindId<Num> id)
        {
            { a.decodeJSON(id) } -> std::same_as<void>;
        };

        template <size_t... As, size_t... Bs>
        constexpr std::index_sequence<As..., Bs...> operator+(std::index_sequence<As...>, std::index_sequence<Bs...>)
        {
            return {};
        }
        template <class Type, size_t LineNum>
        constexpr auto filter_seq()
        {
            if constexpr (IsJSONBindIdCallable<Type, LineNum>) {
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
            return make_sequence_impl<Type>(std::make_index_sequence<AUTO_JSON_BINDABLE_MAX_LINES>());
        }

        template<class Type>
        concept IsAutoJSONBindable = decltype(make_sequence<Type>())::size() > 0;

        template<IsAutoJSONBindable Type, size_t Num>
        void auto_bind(Type& ret, const s3d::JSON& json)
        {
            ret.decodeJSON(JSONBindId<Num>{json});
        }
        template<IsAutoJSONBindable Type, size_t ...Seq>
        void auto_bind_all_impl([[maybe_unused]] Type& ret, const s3d::JSON& json, std::index_sequence<Seq...>)
        {
            (auto_bind<Type, Seq>(ret, json), ...);
        }
        template<IsAutoJSONBindable Type>
        void auto_bind_all(Type& ret, const s3d::JSON& json)
        {
            auto_bind_all_impl(ret, json, make_sequence<Type>());
        }

        template<class Type>
        Type Get(const s3d::JSON& json)
        {
            return JSONValueTraits<Type>{}.fromJSON(json);
        }

        template<class Type>
        struct JSONDecoder
        {
            static Type Decode(const s3d::JSON& json, const s3d::String& key)
            {
                return Get<Type>(json[key]);
            }
        };
        template<class Type>
        struct JSONDecoder<s3d::Optional<Type>>
        {
            static s3d::Optional<Type> Decode(const s3d::JSON& json, const s3d::String& key)
            {
                if (!json.hasElement(key)) {
                    return s3d::none;
                }
                return Get<s3d::Optional<Type>>(json[key]);
            }
        };
    }
    template<detail::jsonbind::IsJSONBindable Type>
    struct JSONValueTraits<Type>
    {
        Type fromJSON(const s3d::JSON& value) const
        {
            return JSONBind<Type>{}.fromJSON(value);
        }
    };
    template<detail::jsonbind::IsAutoJSONBindable Type>
    struct JSONBind<Type>
    {
        Type fromJSON(const s3d::JSON& json)
        {
            Type ret{};
            detail::jsonbind::auto_bind_all(ret, json);
            return ret;
        }
    };
}

//----------------------------------------
// Macro
//----------------------------------------

#define JSON_BIND_IMPL_OVERLOAD(e1, e2, NAME, ...) NAME
#define JSON_BIND_IMPL_2(Value, JSONKey)\
]]  void decodeJSON(const ::abyss::detail::jsonbind::JSONBindId<__LINE__>& id)\
{\
    static_assert(__LINE__ - 2 < ::abyss::detail::jsonbind::AUTO_JSON_BINDABLE_MAX_LINES);\
    using Type = decltype(Value);\
    Value = ::abyss::detail::jsonbind::JSONDecoder<Type>::Decode(id.json, U##JSONKey);\
}[[

#define JSON_BIND_IMPL_1(Value) JSON_BIND_IMPL_2(Value, #Value)
#define JSON_BIND_PP_EXPAND( x ) x

#define JSON_BIND(...) JSON_BIND_PP_EXPAND(JSON_BIND_IMPL_OVERLOAD(__VA_ARGS__, JSON_BIND_IMPL_2, JSON_BIND_IMPL_1)(__VA_ARGS__))

