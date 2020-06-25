#include "SmoothCircle.hpp"
#include <abyss/views/UI/Fade/SmoothCircleVM/SmoothCircleVM.hpp>
#include <abyss/controllers/UI/UIOrder.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/Camera/Camera.hpp>

namespace abyss::ui::Fade
{
    SmoothCircle::SmoothCircle():
        m_view(std::make_unique<SmoothCircleVM>())
    {
        this->m_order = UIOrder::Fade;
    }
    SmoothCircle& SmoothCircle::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }
    SmoothCircle& SmoothCircle::setFadeTime(double fadeTimeSec)
    {
        m_fadeTimeSec = fadeTimeSec;
        return *this;
    }
    SmoothCircle& SmoothCircle::setIsFadeOut(bool isFadeOut)
    {
        m_isFadeOut = isFadeOut;
        return *this;
    }
    SmoothCircle& SmoothCircle::setIsFadeIn(bool isFadeIn)
    {
        return this->setIsFadeOut(!isFadeIn);
    }
    void SmoothCircle::draw() const
    {
        // 座標を修正する
        auto pos = m_pManager->getModule<Camera>()->transform(m_pos);
        m_view
            ->setPos(pos)
            .setFadeTimeSec(m_fadeTimeSec)
            .setIsFadeOut(m_isFadeOut)
            .draw();
    }
}
