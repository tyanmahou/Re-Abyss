#include <abyss/components/Event/Common/FadeIrisOut.hpp>

#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/UI/UIs.hpp>

#include <abyss/components/UI/Fade/IrisOut/Builder.hpp>
#include <abyss/components/UI/Fade/IrisOut/FadeCtrl.hpp>

namespace abyss::Event
{
    FadeIrisOut::FadeIrisOut(EventObj* pEvent, bool createOnStart):
        m_pEvent(pEvent),
        m_createOnStart(createOnStart)
    {}

    void FadeIrisOut::onStart()
    {
        if (m_createOnStart) {
            this->create();
        }
    }

    void FadeIrisOut::onEnd()
    {
        this->destroy();
    }

    void FadeIrisOut::create()
    {
        if (!m_fadeUI) {
            m_fadeUI = m_pEvent->getModule<UIs>()
                ->create<UI::Fade::IrisOut::Builder>()
                ->find<UI::Fade::IrisOut::FadeCtrl>()
                ;
        }
    }

    void FadeIrisOut::destroy()
    {
        if (m_fadeUI) {
            m_fadeUI->destroy();
            m_fadeUI = nullptr;
        }
    }
    FadeIrisOut& FadeIrisOut::setIsFadeIn(bool fadeIn)
    {
        if (m_fadeUI) {
            m_fadeUI->setIsFadeIn(fadeIn);
        }
        return *this;
    }
    FadeIrisOut& FadeIrisOut::setPos(const s3d::Vec2 & pos)
    {
        if (m_fadeUI) {
            m_fadeUI->setPos(pos);
        }
        return *this;
    }
    FadeIrisOut& FadeIrisOut::setFadeTime(double time)
    {
        if (m_fadeUI) {
            m_fadeUI->setFadeTime(time);
        }
        return *this;
    }
    FadeIrisOut& FadeIrisOut::setColor(const s3d::ColorF& color)
    {
        if (m_fadeUI) {
            m_fadeUI->setColor(color);
        }
        return *this;
    }
}
