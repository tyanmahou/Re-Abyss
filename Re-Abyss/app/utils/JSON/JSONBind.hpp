#pragma once
#include <concepts>
#include <Siv3D/JSON.hpp>

namespace abyss
{
    namespace detail::jsonbind {
        template<class Type>
        Type FromJSON(const s3d::JSON& value);

        template<class Type>
        s3d::JSON ToJSON(const Type& value);
    }

    template<class Type>
    struct JSONValueTraits
    {
        Type fromJSON(const s3d::JSON& value) const
        {
            return value.get<Type>();
        }
        s3d::JSON toJSON(const Type& value) const
        {
            return value;
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
            return detail::jsonbind::FromJSON<Type>(value);
        }

        s3d::JSON toJSON(const s3d::Optional<Type>& value) const
        {
            if (value) {
                return detail::jsonbind::ToJSON(*value);
            }
            return nullptr;
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
                    ret << detail::jsonbind::FromJSON<Type>(object);
                }
            }
            return ret;
        }

        s3d::JSON toJSON(const s3d::Array<Type, Allocator>& value) const
        {
            return value.map([](const Type& v) {
                return detail::jsonbind::ToJSON(v);
            });
        }
    };

    template<class Type>
    struct JSONBind
    {
        // Type fromJSON(const s3d::JSON& value) const
        // s3d::JSON toJSON(const Type& value) const
    };

    namespace detail::jsonbind
    {
        inline constexpr size_t AUTO_JSON_BINDABLE_MAX_LINES = 500;

        template<size_t Num, bool Encode = false>
        struct JSONBindId
        {
            enum : size_t
            {
                Value = Num
            };
            const s3d::JSON& json;
        };
        template<size_t Num>
        struct JSONBindId<Num, true>
        {
            enum : size_t
            {
                Value = Num
            };
            s3d::JSON& json;
        };

        template<class Type>
        concept JSONDecodable = requires(const s3d::JSON & json)
        {
            { JSONBind<Type>{}.fromJSON(json) }->std::same_as<Type>;
        };
        template<class Type>
        concept JSONEncodable = requires(const Type & value)
        {
            { JSONBind<Type>{}.toJSON(value) }->std::same_as<s3d::JSON>;
        };
        template<class Type>
        concept JSONBindable = JSONDecodable<Type> || JSONEncodable<Type>;


        template<class Type, int Num>
        concept AutoJSONBindIdDecodable = requires(Type a, JSONBindId<Num, false> id)
        {
            { a.decodeJSON(id, nullptr) } -> std::same_as<void>;
        };
        template<class Type, int Num>
        concept AutoJSONBindIdEncodable = requires(Type a, JSONBindId<Num, true> id)
        {
            { a.encodeJSON(id, nullptr) } -> std::same_as<void>;
        };

        template <size_t... As, size_t... Bs>
        constexpr std::index_sequence<As..., Bs...> operator+(std::index_sequence<As...>, std::index_sequence<Bs...>)
        {
            return {};
        }
        template <class Type, bool Encode, size_t LineNum>
        constexpr auto filter_seq()
        {
            if constexpr (Encode && AutoJSONBindIdEncodable<Type, LineNum>) {
                return std::index_sequence<LineNum>{};
            } else if constexpr (!Encode && AutoJSONBindIdDecodable<Type, LineNum>) {
                return std::index_sequence<LineNum>{};
            } else {
                return std::index_sequence<>{};
            }
        }
        template <class Type, bool Encode, size_t ...Seq>
        constexpr auto make_sequence_impl(std::index_sequence<Seq...>)
        {
            return (filter_seq<Type, Encode, Seq>() + ...);
        }

        template <class Type, bool Encode>
        constexpr auto make_sequence()
        {
            return make_sequence_impl<Type, Encode>(std::make_index_sequence<AUTO_JSON_BINDABLE_MAX_LINES>());
        }

        template<class Type>
        concept AutoJSONDecodable = decltype(make_sequence<Type, false>())::size() > 0;

        template<class Type>
        concept AutoJSONEncodable = decltype(make_sequence<Type, true>())::size() > 0;

        template<class Type>
        concept AutoJSONBindable = AutoJSONDecodable<Type> || AutoJSONEncodable<Type>;

        template<AutoJSONDecodable Type, size_t Num>
        void auto_bind_decode(Type& ret, const s3d::JSON& json)
        {
            ret.decodeJSON(JSONBindId<Num, false>{json}, nullptr);
        }

        template<AutoJSONDecodable Type, size_t ...Seq>
        void auto_bind_decode_all_impl(Type& ret, const s3d::JSON& json, std::index_sequence<Seq...>)
        {
            (auto_bind_decode<Type, Seq>(ret, json), ...);
        }
        template<AutoJSONDecodable Type>
        void auto_bind_decode_all(Type& ret, const s3d::JSON& json)
        {
            auto_bind_decode_all_impl(ret, json, make_sequence<Type, false>());
        }

        template<AutoJSONEncodable Type, size_t Num>
        void auto_bind_encode(const Type& ret, s3d::JSON& json)
        {
            ret.encodeJSON(JSONBindId<Num, true>{json}, nullptr);
        }

        template<AutoJSONEncodable Type, size_t ...Seq>
        void auto_bind_encode_all_impl(const Type& ret, s3d::JSON& json, std::index_sequence<Seq...>)
        {
            (auto_bind_encode<Type, Seq>(ret, json), ...);
        }
        template<AutoJSONEncodable Type>
        void auto_bind_encode_all(const Type& ret, s3d::JSON& json)
        {
            auto_bind_encode_all_impl(ret, json, make_sequence<Type, true>());
        }

        template<class Type>
        Type FromJSON(const s3d::JSON& json)
        {
            return JSONValueTraits<Type>{}.fromJSON(json);
        }

        template<class Type>
        s3d::JSON ToJSON(const Type& value)
        {
            return JSONValueTraits<Type>{}.toJSON(value);
        }
        template<class Type>
        struct JSONDecoder
        {
            static Type Decode(const s3d::JSON& json, const s3d::String& key)
            {
                return FromJSON<Type>(json[key]);
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
                return FromJSON<s3d::Optional<Type>>(json[key]);
            }
        };

        template<class Type>
        concept ConvertFromJSON = requires(s3d::JSON json) {
            {FromJSON<Type>(json)}->std::same_as<Type>;
        };
        template<class Type>
        concept ConvertToJSON = requires(Type value) {
            {ToJSON<Type>(value)}->std::same_as<s3d::JSON>;
        };
    }
    template<detail::jsonbind::JSONBindable Type>
    struct JSONValueTraits<Type>
    {
        Type fromJSON(const s3d::JSON& value) const requires detail::jsonbind::JSONDecodable<Type>
        {
            return JSONBind<Type>{}.fromJSON(value);
        }
        s3d::JSON toJSON(const Type& value) const requires detail::jsonbind::JSONEncodable<Type>
        {
            return JSONBind<Type>{}.toJSON(value);
        }
    };
    template<detail::jsonbind::AutoJSONBindable Type>
    struct JSONBind<Type>
    {
        Type fromJSON(const s3d::JSON& json) const requires detail::jsonbind::AutoJSONDecodable<Type>
        {
            Type ret{};
            detail::jsonbind::auto_bind_decode_all(ret, json);
            return ret;
        }
        s3d::JSON toJSON(const Type& value) const requires detail::jsonbind::AutoJSONEncodable<Type>
        {
            s3d::JSON ret{};
            detail::jsonbind::auto_bind_encode_all(value, ret);
            return ret;
        }
    };
}

//----------------------------------------
// Macro
//----------------------------------------

#define JSON_BIND_IMPL_OVERLOAD(e1, e2, NAME, ...) NAME
#define JSON_BIND_IMPL_2(Value, JSONKey)\
]]  void decodeJSON(const ::abyss::detail::jsonbind::JSONBindId<__LINE__, false>& id, auto = nullptr)\
{\
    static_assert(__LINE__ - 2 < ::abyss::detail::jsonbind::AUTO_JSON_BINDABLE_MAX_LINES);\
    using Type = decltype(Value);\
    Value = ::abyss::detail::jsonbind::JSONDecoder<Type>::Decode(id.json, U##JSONKey);\
}\
 void encodeJSON(const ::abyss::detail::jsonbind::JSONBindId<__LINE__, true>& id, auto = nullptr) const \
{\
    static_assert(__LINE__ - 2 < ::abyss::detail::jsonbind::AUTO_JSON_BINDABLE_MAX_LINES);\
    using Type = decltype(Value);\
    id.json[U##JSONKey] = ::abyss::detail::jsonbind::ToJSON(Value);\
}[[

#define JSON_BIND_IMPL_1(Value) JSON_BIND_IMPL_2(Value, #Value)
#define JSON_BIND_PP_EXPAND( x ) x

#define JSON_BIND(...) JSON_BIND_PP_EXPAND(JSON_BIND_IMPL_OVERLOAD(__VA_ARGS__, JSON_BIND_IMPL_2, JSON_BIND_IMPL_1)(__VA_ARGS__))

