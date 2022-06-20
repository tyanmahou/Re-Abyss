#pragma once
#include <Siv3D/String.hpp>

namespace abyss
{
    /// <summary>
    /// 一時保存に仕様するキー
    /// </summary>
    class TempKey
    {
        friend struct std::hash<TempKey>;
    public:
        static TempKey ItemGet(s3d::uint32 id);
    public:
        [[nodiscard]] auto operator <=>(const TempKey& other) const = default;
    private:
        TempKey(const s3d::String& key) :
            m_key(key)
        {}
    private:
        s3d::String m_key;
    };
}

namespace std
{
    template<>
    struct hash<abyss::TempKey>
    {
        [[nodiscard]] std::size_t operator()(const abyss::TempKey& key) const
        {
            return std::hash<s3d::String>{}(key.m_key);
        }
    };
}