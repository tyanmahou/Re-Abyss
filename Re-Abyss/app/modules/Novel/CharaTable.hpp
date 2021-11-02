#pragma once
#include <abyss/models/Novel/CharaModel.hpp>
#include <abyss/types/Novel/Face.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::Novel
{
    /// <summary>
    /// ノベルアクターの種類
    /// </summary>
    class CharaTable
    {
    public:
        CharaTable();

        void add(const CharaModel& chara);

        [[nodiscard]] bool isContain(CharaKind kind) const;
        [[nodiscard]] const CharaModel& get(CharaKind kind) const;

        [[nodiscard]] s3d::Optional<CharaModel> find(CharaKind kind) const;

    private:
        s3d::HashTable<CharaKind, CharaModel> m_table;
    };
}