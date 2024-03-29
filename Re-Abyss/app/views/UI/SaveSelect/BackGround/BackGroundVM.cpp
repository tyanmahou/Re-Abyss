#include <abyss/views/UI/SaveSelect/BackGround/BackGroundVM.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/commons/Constants.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::SaveSelect::BackGround
{
    BackGroundVM::BackGroundVM():
        m_texture(Resource::Assets::Main()->load(U"UI/SaveSelect/Bg.png")),
        m_fade(Resource::Assets::Main()->load(U"UI/SaveSelect/DotFade.png")),
        m_horizon(Resource::Assets::Main()->load(U"UI/SaveSelect/Horizon.png")),
        m_pos(AnchorUtil::FromCc(0, 0))
    {}

    void BackGroundVM::draw(const s3d::Color& color) const
    {
        m_texture.drawAt(m_pos);
        m_fade.drawAt(m_pos, color);
        constexpr Vec2 center = AnchorUtil::FromCc(0, 0);
        m_horizon.drawAt(m_pos + AnchorUtil::FromTc(0, Param::Horizon::Header) - center);
        m_horizon.flipped().drawAt(m_pos + AnchorUtil::FromBc(0, Param::Horizon::Footer) - center);
    }
}