#include <abyss/views/UI/Home/Top/TopView.hpp>
#include <abyss/views/UI/Home/Top/ModeIconVM.hpp>
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
                .setIconOffset(param.iconOffset)
                .setIconScale(param.scale)
                .setText(param.text)
                .setTextOffset(param.textOffset)
                .setFontSize(param.fontSize)
                .setScale(param.scale)
                .setReverseColor(param.isReverseColor);
        }
    }
    TopView::~TopView()
    {}
    void TopView::draw() const
    {
        for (size_t index = 0; index < IconSize; ++index) {
            m_icons[index]
                .setSelected(index == static_cast<size_t>(m_mode))
                .draw();
        }
    }
}
