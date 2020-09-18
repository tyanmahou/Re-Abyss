#include "CursorVM.hpp"
#include <abyss/commons/ResourceManager/ResourceManager.hpp>

namespace abyss::Cycle::Title::Cursor
{
    CursorVM::CursorVM() :
        m_texture(ResourceManager::Main()->loadTexturePacker(U"actors/Player/player.json"))
    {}

    CursorVM& CursorVM::setPos(const s3d::Vec2& pos)
    {
        m_pos = pos;
        return *this;
    }

    void CursorVM::draw() const
    {
        m_texture(U"stay_atk")({ 0, 80 }, { 80, 80 })
            .drawAt(m_pos);
    }
}