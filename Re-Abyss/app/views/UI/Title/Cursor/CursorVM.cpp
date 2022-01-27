#include <abyss/views/UI/Title/Cursor/CursorVM.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>

namespace abyss::UI::Title::Cursor
{
    CursorVM::CursorVM() :
        m_texture(Resource::Assets::Main()->load(U"Actor/Player/Player.json"))
    {}

    void CursorVM::draw() const
    {
        m_texture(U"stay_atk")({ 0, 80 }, { 80, 80 })
            .drawAt(m_pos);
    }
}