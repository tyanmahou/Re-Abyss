#include <abyss/views/UI/Home/Top/TopView.hpp>
#include <abyss/views/UI/Home/Top/ModeIconVM.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/SeekThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/GuildThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/MaintThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/MemoryThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/CollectThumb.hpp>
#include <abyss/views/UI/Home/Top/ModeIcon/OptionThumb.hpp>

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
                .setText(param.text)
                .setTextOffset(param.textOffset)
                .setFontSize(param.fontSize)
                .setScale(param.scale)
                .setReverseColor(param.isReverseColor)
                .setLocked(true)
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
        for (size_t index = 0; index < IconSize; ++index) {
            m_icons[index]
                .setTime(m_time)
                .setSelected(index == static_cast<size_t>(m_mode))
                .draw();
        }
    }
}
