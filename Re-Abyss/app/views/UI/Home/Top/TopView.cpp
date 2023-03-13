#include <abyss/views/UI/Home/Top/TopView.hpp>
#include <abyss/views/UI/Home/Top/ModeIconVM.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/SeekThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/GuildThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/MaintThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/MemoryThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/CollectThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/OptionThumb.hpp>
#include <abyss/views/UI/Home/Top/ColorDef.hpp>

#include <abyss/params/UI/Home/Top/ViewParam.hpp>

namespace abyss::UI::Home::Top
{
    TopView::TopView():
        m_icons(std::make_unique<ModeIconVM[]>(IconSize))
    {
        for (size_t index = 0; index < IconSize; ++index) {
            const auto& param = ViewParam::Icons[index];
            m_icons[index]
                .setPos(param.pos)
                .setScale(param.scale)
                .setReverseColor(param.isReverseColor)
                //.setLocked(true)
                ;
        }
        m_icons[IconSeek].setThumbnail<SeekThumb>();
        m_icons[IconGuild].setThumbnail<GuildThumb>();
        m_icons[IconMaint].setThumbnail<MaintThumb>();
        m_icons[IconMemory].setThumbnail<MemoryThumb>();
        m_icons[IconCollect].setThumbnail<CollectThumb>();
        m_icons[IconOption].setThumbnail<OptionThumb>();
    }
    TopView::~TopView()
    {}
    void TopView::draw() const
    {
        // BackLine
        {
            const auto& param = ViewParam::Icons[static_cast<size_t>(m_mode)];
            const auto animeRate = s3d::Min(m_time, 0.3) / 0.3;

            auto t2d = Transformer2D(s3d::Mat3x2::Rotate(-s3d::Math::QuarterPi, param.pos));
            Line(param.line0.begin, s3d::Math::Lerp(param.line0.begin, param.line0.end, animeRate))
                .moveBy(param.pos)
                .draw(ColorDef::Color1);
            Line(param.line1.begin, s3d::Math::Lerp(param.line1.begin, param.line1.end, animeRate))
                .moveBy(param.pos)
                .draw(ColorDef::Color1);

            // Text
            {
                constexpr Vec2 baseSize{ 160, 160 };
                Vec2 size = baseSize * param.scale;

                const auto animeRate = s3d::Min(m_time, 0.2) / 0.2;
                const auto animOffs = s3d::Math::Lerp(Vec2{ -10, 0 }, Vec2{ 0, 0 }, animeRate);
                FontAsset(U"pm12b-20")(false ? U"???" : param.text)
                    .draw(param.pos - size / 2 + param.textOffset + animOffs, ColorF(ColorDef::Color1, animeRate));
            }
        }
        for (size_t index = 0; index < IconSize; ++index) {
            m_icons[index]
                .setTime(m_time)
                .setSelected(index == static_cast<size_t>(m_mode))
                .draw();
        }
    }
}
