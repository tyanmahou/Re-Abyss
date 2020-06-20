#include "SmoothCircleVM.hpp"
#include <abyss/views/util/Fade/Fade.hpp>
#include <abyss/commons/Constants.hpp>
#include <Siv3D.hpp>

namespace abyss::ui::Fade
{
    void SmoothCircleVM::draw() const
    {
        if (m_isFadeOut) {
            FadeOut(abyss::Fade::SmoothCircle, m_fadeTimeSec, m_pos);
        } else {
            FadeIn(abyss::Fade::SmoothCircle, m_fadeTimeSec, m_pos);
        }
    }

}
