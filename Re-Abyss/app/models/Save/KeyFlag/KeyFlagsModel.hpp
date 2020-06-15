#pragma once
#include <Siv3D/HashTable.hpp>
#include <abyss/models/Save/KeyFlag/SaveLevel.hpp>

namespace abyss
{
    //
    class KeyFlagsModel
    {
        s3d::HashTable<s3d::String, SaveLevel> m_flags;
    public:
        KeyFlagsModel() = default;

        bool add(const s3d::String& key, SaveLevel level);

        bool isContain(const s3d::String& key) const;

        void clear(SaveLevel level = SaveLevel::Never);
    };
}