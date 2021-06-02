#pragma once
#include <Siv3D/HashTable.hpp>
#include <abyss/types/Temporary/TempLevel.hpp>
#include <abyss/types/Temporary/TempKey.hpp>

namespace abyss
{
    /// <summary>
    /// フラグ
    /// </summary>
    class TempFlagsModel
    {
        s3d::HashTable<TempKey, TempLevel> m_flags;
    public:
        TempFlagsModel() = default;

        bool add(const TempKey& key, TempLevel level);

        bool isContain(const TempKey& key) const;

        void clear(TempLevel level = TempLevel::Never);
    };
}