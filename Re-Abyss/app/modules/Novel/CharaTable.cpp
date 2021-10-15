#include "CharaTable.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Novel
{
    CharaTable::CharaTable()
    {
        // @todo 外部からロードになる
        m_table[CharaKind::Player]
            .setKind(CharaKind::Player)
            .setName(U"Player")
            .setFacePath(U"actors/Player/face.json");
        m_table[CharaKind::CodeZero]
            .setKind(CharaKind::CodeZero)
            .setName(U"CodeZero")
            .setFacePath(U"actors/Enemy/CodeZero/face.json");
        m_table[CharaKind::DrQuery]
            .setKind(CharaKind::DrQuery)
            .setName(U"DrQuery")
            .setFacePath(U"actors/Enemy/DrQuery/face.json");
    }
    void CharaTable::add(const CharaModel& chara)
    {
        m_table[chara.getKind()] = chara;
    }
    bool CharaTable::isContain(CharaKind kind) const
    {
        return m_table.contains(kind);
    }
    const CharaModel& CharaTable::getChara(CharaKind kind) const
    {
        return m_table.at(kind);
    }
}
