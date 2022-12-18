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
        /// <summary>
        /// アイテム取得
        /// </summary>
        /// <param name="mapName"></param>
        /// <param name="id"></param>
        /// <returns></returns>
        static TempKey ItemGet(const s3d::String& mapName, s3d::uint32 id);

        /// <summary>
        /// 中ボス撃破
        /// </summary>
        /// <param name="mapName"></param>
        /// <param name="id"></param>
        /// <returns></returns>
        static TempKey MidBossKill(const s3d::String& mapName, s3d::uint32 id);

        /// <summary>
        /// イベント完了
        /// </summary>
        /// <param name="mapName"></param>
        /// <param name="id"></param>
        /// <returns></returns>
        static TempKey EventComplete(const s3d::String& mapName, s3d::uint32 id);

        /// <summary>
        /// シャッター破壊
        /// </summary>
        /// <param name="mapName"></param>
        /// <param name="id"></param>
        /// <returns></returns>
        static TempKey ShutterWallBreak(const s3d::String& mapName, s3d::uint32 id);
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
