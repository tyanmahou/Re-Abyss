#include <abyss/views/UI/GamePause/BackGround/BackGroundVM.hpp>

#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/UI/SaveSelect/Param.hpp>
#include <abyss/views/util/Pivot/PivotUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::GamePause::BackGround
{
    using namespace abyss::UI::SaveSelect;

    BackGroundVM::BackGroundVM():
        m_texture(Resource::Assets::Main()->load(U"UI/SaveSelect/Bg.png")),
        m_horizon(Resource::Assets::Main()->load(U"UI/SaveSelect/Horizon.png")),
        m_pos(PivotUtil::FromCc(0, 0)),
        m_bgColor(1, 1)
    {}

    void BackGroundVM::draw() const
    {
        m_texture.drawAt(m_pos, m_bgColor);
        constexpr Vec2 center = PivotUtil::FromCc(0, 0);
        m_horizon.drawAt(m_pos + PivotUtil::FromTc(0, Param::Horizon::Header) - center);
        m_horizon.flipped().drawAt(m_pos + PivotUtil::FromBc(0, Param::Horizon::Footer) - center);
    }
}
