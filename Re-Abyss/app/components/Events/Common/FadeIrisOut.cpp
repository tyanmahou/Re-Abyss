#include "FadeIrisOut.hpp"

#include <abyss/modules/Event/base/IEvent.hpp>
#include <abyss/modules/UI/UI.hpp>

#include <abyss/components/UI/Fade/IrisOut/Builder.hpp>
#include <abyss/components/UI/Fade/IrisOut/FadeCtrl.hpp>

namespace abyss::Event
{
    FadeIrisOut::FadeIrisOut(IEvent* pEvent, bool createOnStart):
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
            m_fadeUI = m_pEvent->getModule<UI>()
                ->create<ui::Fade::IrisOut::Builder>()
                ->find<ui::Fade::IrisOut::FadeCtrl>()
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
}
