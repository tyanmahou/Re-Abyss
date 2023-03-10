#include <abyss/views/UI/Home/Top/ModeIcon/MemoryThumb.hpp>
#include <abyss/commons/Resource/Assets/Assets.hpp>
#include <abyss/params/UI/Home/Top/ViewParam.hpp>

namespace abyss::UI::Home::Top
{
    MemoryThumb::MemoryThumb() :
        m_texture(Resource::Assets::Main()->load(U"UI/Home/ModeIcon.json"))
    {
    }
    void MemoryThumb::drawUnselected(const s3d::Vec2& pos, [[maybe_unused]] double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::MemoryIcon();

        m_texture(U"memory_off_inv")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[0]);
        m_texture(U"memory_off")
            .scaled(viewParam.iconScale)
            .drawAt(pos + viewParam.iconOffset, colors[1]);
    }
    void MemoryThumb::drawSelected(const s3d::Vec2& pos, double time, const s3d::ColorF(&colors)[2]) const
    {
        const auto& viewParam = ViewParam::MemoryIcon();
        auto addScale = 1.0 + 0.1 * s3d::Saturate(time * 5);
        auto posOffset = -10.0 * s3d::Saturate(time * 5) + s3d::Periodic::Sine0_1(5s, time) * -10.0;
        m_texture(U"memory_on_inv")
            .scaled(viewParam.iconScale * addScale)
            .drawAt(pos + viewParam.iconOffset + Vec2{0, posOffset}, colors[0]);
        m_texture(U"memory_on")
            .scaled(viewParam.iconScale * addScale)
            .drawAt(pos + viewParam.iconOffset + Vec2{ 0, posOffset }, colors[1]);
    }
}
