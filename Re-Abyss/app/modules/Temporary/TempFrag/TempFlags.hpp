#pragma once
#include <Siv3D/HashTable.hpp>
#include <Siv3D/HashSet.hpp>
#include <abyss/modules/Temporary/TempFrag/TempLevel.hpp>
#include <abyss/modules/Temporary/TempFrag/TempKey.hpp>

namespace abyss
{
    /// <summary>
    /// フラグ
    /// </summary>
    class TempFlags
    {
    public:
        TempFlags() = default;

        bool add(const TempKey& key, TempLevel level);

        bool isContain(const TempKey& key) const;

        void clear(TempLevel level = TempLevel::Never);
    private:
        s3d::HashTable<TempLevel, s3d::HashSet<TempKey>> m_flags;
    };
}
