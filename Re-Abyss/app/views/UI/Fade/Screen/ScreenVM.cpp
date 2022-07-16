#include <abyss/views/UI/Fade/Screen/ScreenVM.hpp>
#include <abyss/views/util/Fade/Fade.hpp>

namespace abyss::UI::Fade::Screen
{
    void ScreenVM::draw() const
    {
        auto shader = m_shader
            .setIsShape(true)
            .start();

        if (m_isFadeOut) {
            FadeOut(abyss::Fade::Default, m_fadeTimeSec);
        } else {
            FadeIn(abyss::Fade::Default, m_fadeTimeSec);
        }
    }
}
