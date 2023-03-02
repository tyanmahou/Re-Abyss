#pragma once
#include <abyss/models/Adv/Chara.hpp>
#include <abyss/values/Adv/Emote.hpp>
#include <abyss/utils/TexturePacker/TexturePacker.hpp>
#include <Siv3D/HashTable.hpp>

namespace abyss::Adv
{
    /// <summary>
    /// ノベルアクターの種類
    /// </summary>
    class CharaTable
    {
    public:
        CharaTable();

        void add(const Chara& chara);

        [[nodiscard]] bool isContain(CharaKind kind) const;
        [[nodiscard]] const Chara& get(CharaKind kind) const;

        [[nodiscard]] s3d::Optional<Chara> find(CharaKind kind) const;

    private:
        s3d::HashTable<CharaKind, Chara> m_table;
    };
}
