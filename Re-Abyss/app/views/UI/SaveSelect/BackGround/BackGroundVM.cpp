#include "BackGroundVM.hpp"
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::BackGround
{
    BackGroundVM::BackGroundVM():
        m_texture(Resource::Assets::Main()->loadTexture(U"ui/SaveSelect/bg.png")),
        m_fade(Resource::Assets::Main()->loadTexture(U"ui/SaveSelect/dot_fade.png")),
        m_horizon(Resource::Assets::Main()->loadTexture(U"ui/SaveSelect/horizon.png")),
        m_pos(Constants::AppResolutionF / 2.0)
    {}

    void BackGroundVM::draw(const s3d::Color& color) const
    {
        m_texture.drawAt(m_pos);
        m_fade.drawAt(m_pos, color);
        m_horizon.drawAt(m_pos + s3d::Vec2::UnitY() * Param::Horizon::Header);
        m_horizon.flipped().drawAt(m_pos + s3d::Vec2::UnitY() * Param::Horizon::Footer);
    }
}