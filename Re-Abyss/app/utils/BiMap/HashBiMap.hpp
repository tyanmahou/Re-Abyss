#pragma once
#include <Siv3D/HashTable.hpp>
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
        class Value
    >
    class HashBiMap
    {
    public:
        /// <summary>
        /// 要素構築
        /// </summary>
        /// <param name="key"></param>
        /// <param name="value"></param>
        void emplace(const Key& key, const Value& value)
        {
            m_k2v.emplace(key, value);
            m_v2k.emplace(value, key);
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
            return std::forward_like<Self>(self.m_k2v.at(key));
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
            return std::forward_like<Self>(self.m_v2k.at(value));
        }
    private:
        s3d::HashTable<Key, Value> m_k2v;
        s3d::HashTable<Value, Key> m_v2k;
    };
}
