#include <abyss/components/UI/Fade/Screen/FadeCtrl.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/views/UI/Fade/Screen/ScreenVM.hpp>

namespace abyss::UI::Fade::Screen
{
    FadeCtrl::FadeCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<ScreenVM>())
    {}
    FadeCtrl::~FadeCtrl()
    {}
    FadeCtrl& FadeCtrl::setFadeTime(double fadeTimeSec)
    {
        m_fadeTimeSec = fadeTimeSec;
        return *this;
    }
    FadeCtrl& FadeCtrl::setIsFadeOut(bool isFadeOut)
    {
        m_isFadeOut = isFadeOut;
        return *this;
    }
    FadeCtrl& FadeCtrl::setIsFadeIn(bool isFadeIn)
    {
        return this->setIsFadeOut(!isFadeIn);
    }
    void FadeCtrl::destroy()
    {
        m_pUi->destroy();
    }
    void FadeCtrl::onDraw() const
    {
        m_view
            ->setFadeTimeSec(m_fadeTimeSec)
            .setIsFadeOut(m_isFadeOut)
            .draw();
    }
}
