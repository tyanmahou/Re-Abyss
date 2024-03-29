#include <abyss/views/UI/Title/BackGround/BackGroundVM.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Title::BackGround
{
    BackGroundVM::BackGroundVM() :
        m_texture(Resource::Assets::Main()->load(U"UI/Title/Bg.png"))
    {}

    void BackGroundVM::draw() const
    {
        m_texture.drawAt(m_pos, ColorF(1, Periodic::Sine0_1(5s) * 0.3 + 0.7));
    }
}
