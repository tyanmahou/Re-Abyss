#include "FadeIrisOut.hpp"
#include <abyss/views/UI/Fade/IrisOut/IrisOutVM.hpp>
#include <abyss/modules/UI/base/IUserInterface.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>

namespace abyss::ui::Fade::IrisOut
{
    FadeIrisOut::FadeIrisOut(IUserInterface* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<IrisOutVM>())
    {
    }
    FadeIrisOut& FadeIrisOut::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }
    FadeIrisOut& FadeIrisOut::setFadeTime(double fadeTimeSec)
    {
        m_fadeTimeSec = fadeTimeSec;
        return *this;
    }
    FadeIrisOut& FadeIrisOut::setIsFadeOut(bool isFadeOut)
    {
        m_isFadeOut = isFadeOut;
        return *this;
    }
    FadeIrisOut& FadeIrisOut::setIsFadeIn(bool isFadeIn)
    {
        return this->setIsFadeOut(!isFadeIn);
    }
    void FadeIrisOut::destroy()
    {
        m_pUi->destroy();
    }
    void FadeIrisOut::onDraw() const
    {
        // 座標を修正する
        auto pos = m_pUi->getModule<Camera>()->transform(m_pos);
        m_view
            ->setPos(pos)
            .setFadeTimeSec(m_fadeTimeSec)
            .setIsFadeOut(m_isFadeOut)
            .draw();
    }
}
