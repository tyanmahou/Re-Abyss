#include <abyss/components/UI/Fade/IrisOut/FadeCtrl.hpp>
#include <abyss/views/UI/Fade/IrisOut/IrisOutVM.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>

namespace abyss::UI::Fade::IrisOut
{
    FadeCtrl::FadeCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_view(std::make_unique<IrisOutVM>())
    {}
    FadeCtrl::~FadeCtrl()
    {}
    FadeCtrl& FadeCtrl::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }
    FadeCtrl& FadeCtrl::setFadeTime(double fadeTimeSec)
    {
        m_view->setFadeTimeSec(fadeTimeSec);
        return *this;
    }
    FadeCtrl& FadeCtrl::setIsFadeOut(bool isFadeOut)
    {
        m_view->setIsFadeOut(isFadeOut);
        return *this;
    }
    FadeCtrl& FadeCtrl::setIsFadeIn(bool isFadeIn)
    {
        return this->setIsFadeOut(!isFadeIn);
    }
    FadeCtrl& FadeCtrl::setColor(const s3d::ColorF& color)
    {
        m_view->setColor(color);
        return *this;
    }
    void FadeCtrl::destroy()
    {
        m_pUi->destroy();
    }
    void FadeCtrl::onDraw() const
    {
        // 座標を修正する
        auto pos = m_pUi->getModule<Camera>()->transform(m_pos);
        m_view
            ->setPos(pos)
            .draw();
    }
}
