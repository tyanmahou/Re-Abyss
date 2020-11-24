#include "IrisOut.hpp"
#include <abyss/views/UI/Fade/IrisOut/IrisOutVM.hpp>
#include <abyss/controllers/UI/UIOrder.hpp>
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/Camera/Camera.hpp>

namespace abyss::ui::Fade
{
    IrisOut::IrisOut():
        m_view(std::make_unique<IrisOutVM>())
    {
        this->m_order = UIOrder::Fade;
    }
    IrisOut& IrisOut::setPos(const s3d::Vec2 & pos)
    {
        m_pos = pos;
        return *this;
    }
    IrisOut& IrisOut::setFadeTime(double fadeTimeSec)
    {
        m_fadeTimeSec = fadeTimeSec;
        return *this;
    }
    IrisOut& IrisOut::setIsFadeOut(bool isFadeOut)
    {
        m_isFadeOut = isFadeOut;
        return *this;
    }
    IrisOut& IrisOut::setIsFadeIn(bool isFadeIn)
    {
        return this->setIsFadeOut(!isFadeIn);
    }
    void IrisOut::draw() const
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
