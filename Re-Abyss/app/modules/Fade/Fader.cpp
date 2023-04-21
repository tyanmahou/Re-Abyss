#include <abyss/modules/Fade/Fader.hpp>
#include <abyss/scenes/Fade/SceneFader.hpp>

namespace abyss::Fade
{
    Fader::Fader(SceneFader* fader):
        m_fader(fader)
    {
    }
    std::shared_ptr<ScreenFade> Fader::fadeOutScreen(double timeSec) const
    {
        auto fade = std::make_shared<ScreenFade>();
        m_fader->set(fade).fadeOut(timeSec);
        return fade;
    }

    std::shared_ptr<IrisOutFade> Fader::fadeInIrisOut(const s3d::Vec2& pos, double timeSec) const
    {
        auto fade = std::make_shared<IrisOutFade>();
        fade->setPos(pos);
        m_fader->set(fade).fadeIn(timeSec);
        return fade;
    }

    std::shared_ptr<IrisOutFade> Fader::fadeOutIrisOut(const s3d::Vec2& pos, double timeSec) const
    {
        auto fade = std::make_shared<IrisOutFade>();
        fade->setPos(pos);
        m_fader->set(fade).fadeOut(timeSec);
        return fade;
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
