#include <abyss/modules/Novel/CharaTable.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Novel
{
    CharaTable::CharaTable()
    {
        // @todo 外部からロードになる
        m_table[CharaKind::Player]
            .setKind(CharaKind::Player)
            .setName(U"Player")
            .setFacePath(U"Actor/Player/face.json");
        m_table[CharaKind::CodeZero]
            .setKind(CharaKind::CodeZero)
            .setName(U"CodeZero")
            .setFacePath(U"Actor/Enemy/CodeZero/face.json");
        m_table[CharaKind::DrQuery]
            .setKind(CharaKind::DrQuery)
            .setName(U"DrQuery")
            .setFacePath(U"Actor/Enemy/DrQuery/face.json");
    }
    void CharaTable::add(const CharaModel& chara)
    {
        m_table[chara.getKind()] = chara;
    }
    bool CharaTable::isContain(CharaKind kind) const
    {
        return m_table.contains(kind);
    }
    s3d::Optional<CharaModel> CharaTable::find(CharaKind kind) const
    {
        if (!isContain(kind)) {
            return s3d::none;
        }
        return this->get(kind);
    }
    const CharaModel& CharaTable::get(CharaKind kind) const
    {
        return m_table.at(kind);
    }
}
