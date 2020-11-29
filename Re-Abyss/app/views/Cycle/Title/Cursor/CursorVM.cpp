#include "CursorVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::Cycle::Title::Cursor
{
    CursorVM::CursorVM() :
        m_texture(Resource::Assets::Main()->loadTexturePacker(U"actors/Player/player.json"))
    {}

    void CursorVM::draw() const
    {
        m_texture(U"stay_atk")({ 0, 80 }, { 80, 80 })
            .drawAt(m_pos);
    }
}