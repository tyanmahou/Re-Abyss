#include <abyss/modules/Adv/Project/CharaTable.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Adv
{
    CharaTable::CharaTable()
    {
    }
    void CharaTable::add(const Chara& chara)
    {
        m_table[chara.getKind()] = chara;
    }
    bool CharaTable::isContain(CharaKind kind) const
    {
        return m_table.contains(kind);
    }
    s3d::Optional<Chara> CharaTable::find(CharaKind kind) const
    {
        if (!isContain(kind)) {
            return s3d::none;
        }
        return this->get(kind);
    }
    const Chara& CharaTable::get(CharaKind kind) const
    {
        return m_table.at(kind);
    }
}
