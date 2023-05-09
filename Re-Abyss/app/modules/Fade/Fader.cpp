#include <abyss/modules/Fade/Fader.hpp>

namespace abyss::Fade
{
    Fader::Fader(SceneFader* fader):
        m_fader(fader)
    {
    }
    void Fader::fadeIn(double timeSec) const
    {
        m_fader->fadeIn(timeSec);
    }

    bool Fader::isFading() const
    {
        return m_fader->isFading();
    }
}
