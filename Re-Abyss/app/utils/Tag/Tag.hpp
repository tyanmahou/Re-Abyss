#pragma once
#include <type_traits>
#include <memory>
#include <abyss/utils/Memory/fixed_ptr.hpp>

namespace abyss
{
    /// <summary>
    /// タグベース
    /// </summary>
    template<class Kind>
    struct ITag
    {
        using KindType = Kind;
    };
    
    /// <summary>
    /// コンセプト
    /// </summary>
    template<class T, class Kind>
    concept TaggedOf = std::is_base_of_v<ITag<Kind>, T>;

    template<class T>
    concept Tagged = TaggedOf<T, typename T::KindType>;

    /// <summary>
    /// タグ合成
    /// </summary>
    template<class Kind, TaggedOf<Kind>... Args>
    struct Tags : Args...
    {};

    /// <summary>
    /// operator
    /// </summary>
    template<Tagged T, Tagged U>
    constexpr auto operator |(const T&, const U&)
        requires std::same_as<typename T::KindType, typename U::KindType>
    {
        return Tags<typename T::KindType, T, U>{};
    }

    template<class Kind, TaggedOf<Kind> T, TaggedOf<Kind>... Us>
    constexpr auto operator |(const T&, const Tags<Kind, Us...>&)requires std::same_as<typename T::KindType, Kind>
    {
        return Tags<Kind, T, Us...>{};
    }
    template<class Kind, TaggedOf<Kind>... Ts, TaggedOf<Kind> U>
    constexpr auto operator |(const  Tags<Kind, Ts...>&, const U&)
    {
        return Tags<Kind, Ts..., U>{};
    }
    template<class Kind, TaggedOf<Kind>... Ts, TaggedOf<Kind>... Us>
    constexpr auto operator |(const  Tags<Kind, Ts...>&, const Tags<Kind, Us...>&)
    {
        return Tags<Kind, Ts..., Us...>{};
    }

    /// <summary>
    /// タグラッパー
    /// </summary>
    template<class TagPtr>
    class TagType{};

    template<class Kind, class Invalid, class... Type>
    class TagType<fixed_ptr<ITag<Kind>, Invalid, Type...>>
    {
        using TagPtr = fixed_ptr<ITag<Kind>, Invalid, Type...>;
    public:
        TagType() :
            m_tag(TagPtr::template make_fixed<Invalid>())
        {}

        template<TaggedOf<Kind> T>
        TagType([[maybe_unused]] const T&) :
            m_tag(TagPtr::template make_fixed<T>())
        {}

        template<TaggedOf<Kind> T>
        bool is() const
        {
            return fixed_dynamic_cast<T*>(m_tag) != nullptr;
        }

        template<TaggedOf<Kind>... T>
        bool anyOf() const
        {
            if (!m_tag) {
                return false;
            }
            return (... || (fixed_dynamic_cast<T*>(m_tag) != nullptr));
        }

        template<TaggedOf<Kind>... T>
        bool allOf() const
        {
            if (!m_tag) {
                return false;
            }
            return (... && (fixed_dynamic_cast<T*>(m_tag) != nullptr));
        }

        template<TaggedOf<Kind> T>
        bool isNot() const
        {
            return !is<T>();
        }
    private:
        TagPtr m_tag;
    };
}
