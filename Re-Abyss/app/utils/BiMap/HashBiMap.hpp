#pragma once
#include <unordered_map>
#include <variant>

namespace abyss
{
    /// <summary>
    /// 双方向ハッシュマップ
    /// </summary>
    /// <typeparam name="Key"></typeparam>
    /// <typeparam name="Value"></typeparam>
    template<
        class Key,
        class Value,
        class Alloc = std::allocator<std::pair<const std::variant<Key, Value>, std::variant<Key, Value>>>
    >
    class HashBiMap
    {
    public:
        using value_type = std::variant<Key, Value>;
    private:
        template<class T, class U>
        struct Eq
        {
            bool operator ()(const value_type& a, const value_type& b) const noexcept
            {
                return a == b;
            }
        };
        template<class T, class U> requires (!std::same_as<T, U>)
        struct Eq<T, U>
        {
            using is_transparent = void;
            bool operator ()(const T& a, const value_type& b) const noexcept
            {
                return b.index() == 0 && std::get<0>(b) == a;
            }
            bool operator ()(const U& a, const value_type& b) const noexcept
            {
                return b.index() == 1 && std::get<1>(b) == a;
            }
            bool operator ()(const value_type& a, const value_type& b) const noexcept
            {
                return a == b;
            }
        };
        template<class T, class U>
        struct Hash
        {
            std::size_t operator()(const value_type& kv) const
            {
                return std::hash<value_type>{}(kv);
            }
        };
        template<class T, class U> requires (!std::same_as<T, U>)
        struct Hash<T, U>
        {
            using is_transparent = void;
            using transparent_key_equal = Eq<T, U>;
            std::size_t operator()(const value_type& kv) const
            {
                if (kv.index() == 0) {
                    return std::hash<T>{}(std::get<0>(kv));
                } else {
                    return std::hash<U>{}(std::get<1>(kv));
                }
            }
            std::size_t operator()(const T& key) const
            {
                return std::hash<T>{}(key);
            }
            std::size_t operator()(const U& value) const
            {
                return std::hash<U>{}(value);
            }
        };

    public:
        /// <summary>
        /// 要素構築
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        void emplace(const Key& key, const Value& value)
        {
            if constexpr (std::same_as<Key, Value>) {
                value_type k(std::in_place_index<0>, key);
                value_type v(std::in_place_index<1>, value);
                m_data.emplace(k, v);
                m_data.emplace(std::move(v), std::move(k));
            } else {
                m_data.emplace(key, value);
                m_data.emplace(value, key);
            }
        }

        /// <summary>
        /// キーから値取得
        /// </summary>
        /// <typeparam name="Self"></typeparam>
        /// <param name="self"></param>
        /// <param name="key"></param>
        /// <returns></returns>
        template<class Self>
        decltype(auto) value(this Self&& self, const Key& key)
        {
            using iterator_type = decltype(self.m_data.begin());
            iterator_type it{};
            if constexpr (std::same_as<Key, Value>) {
                it = self.m_data.find(value_type{ std::in_place_index<0>, key });
            } else {
                it = self.m_data.find(key);
            }
            if (it == self.m_data.end()) {
                throw std::out_of_range("invalid BidirectionalHashMap::value");
            }
            return std::forward_like<Self>(std::get<1>(it->second));
        }

        /// <summary>
        /// 値からキー取得
        /// </summary>
        /// <typeparam name="Self"></typeparam>
        /// <param name="self"></param>
        /// <param name="value"></param>
        /// <returns></returns>
        template<class Self>
        decltype(auto) key(this Self&& self, const Value& value)
        {
            using iterator_type = decltype(self.m_data.begin());
            iterator_type it{};
            if constexpr (std::same_as<Key, Value>) {
                it = self.m_data.find(value_type{ std::in_place_index<1>, value });
            } else {
                it = self.m_data.find(value);
            }
            if (it == self.m_data.end()) {
                throw std::out_of_range("invalid BidirectionalHashMap::key");
            }
            return std::forward_like<Self>(std::get<0>(it->second));
        }
    private:
        std::unordered_map<value_type, value_type, Hash<Key, Value>, Eq<Key, Value>, Alloc> m_data;
    };
}
