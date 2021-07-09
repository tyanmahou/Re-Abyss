#pragma once
#include <type_traits>
#include <memory>
#include <abyss/utils/FixedPtr/FixedPtr.hpp>

namespace abyss
{
    /// <summary>
    /// タグベース
    /// </summary>
    template<class Kind>
    struct ITag {};
    
    /// <summary>
    /// コンセプト
    /// </summary>
    template<class Kind, class T>
    concept Tagged = std::is_base_of_v<ITag<Kind>, T>;

    /// <summary>
    /// タグ合成
    /// </summary>
    template<class Kind, Tagged<Kind>... Args>
    struct Tags : Args...
    {};

    /// <summary>
    /// operator
    /// </summary>
    template<class Kind, Tagged<Kind> T, Tagged<Kind> U>
    constexpr auto operator |(const T&, const U&)
    {
        return Tags<Kind, T, U>{};
    }
    template<class Kind, Tagged<Kind> T, Tagged<Kind>... Us>
    constexpr auto operator |(const T&, const Tags<Kind, Us...>&)
    {
        return Tags<Kind, T, Us...>{};
    }
    template<class Kind, Tagged<Kind>... Ts, Tagged<Kind> U>
    constexpr auto operator |(const  Tags<Kind, Ts...>&, const U&)
    {
        return Tags<Kind, Ts..., U>{};
    }
    template<class Kind, Tagged<Kind>... Ts, Tagged<Kind>... Us>
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

        template<Tagged<Kind> T>
        TagType([[maybe_unused]] const T&) :
            m_tag(TagPtr::template make_fixed<T>())
        {}

        template<Tagged<Kind> T>
        bool is() const
        {
            return fixed_dynamic_cast<T*>(m_tag) != nullptr;
        }

        template<Tagged<Kind>... T>
        bool anyOf() const
        {
            if (!m_tag) {
                return false;
            }
            return (... || (fixed_dynamic_cast<T*>(m_tag) != nullptr));
        }

        template<Tagged<Kind>... T>
        bool allOf() const
        {
            if (!m_tag) {
                return false;
            }
            return (... && (fixed_dynamic_cast<T*>(m_tag) != nullptr));
        }

        template<Tagged<Kind> T>
        bool isNot() const
        {
            return !is<T>();
        }
    private:
        TagPtr m_tag;
    };
}
