#include <abyss/views/UI/Fade/IrisOut/IrisOutVM.hpp>
#include <abyss/views/util/Fade/Fade.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Fade::IrisOut
{
    void IrisOutVM::draw() const
    {
        m_color.then(abyss::Fade::SetColor);

        if (m_isFadeOut) {
            FadeOut(abyss::Fade::IrisOut, m_fadeTimeSec, m_pos);
        } else {
            FadeIn(abyss::Fade::IrisOut, m_fadeTimeSec, m_pos);
        }
    }

}
