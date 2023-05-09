#include <abyss/modules/Fade/SceneFader.hpp>

namespace abyss::Fade
{
    SceneFader::SceneFader()
    {}
    SceneFader::~SceneFader()
    {}
    SceneFader& SceneFader::set(std::shared_ptr<ISceneFade> fade)
    {
        m_fade = fade;
        return *this;
    }
    void SceneFader::fadeIn(double timeSec)
    {
        m_timer.reset(timeSec);
        m_isFadeIn = true;
    }
    void SceneFader::fadeOut(double timeSec)
    {
        m_timer.reset(timeSec);
        m_isFadeIn = false;
    }
    bool SceneFader::isFading() const
    {
        return !m_timer.isEnd();
    }
    void SceneFader::update(double dt)
    {
        if (!this->isFading()) {
            return;
        }
        m_timer.update(dt);
    }
    void SceneFader::draw() const
    {
        if (!(this->isFading() || !m_isFadeIn)) {
            return;
        }
        if (m_fade) {
            m_fade->onFade(Scene::Rect(), m_isFadeIn ? m_timer.invRate() : m_timer.rate());
        }
    }
}
