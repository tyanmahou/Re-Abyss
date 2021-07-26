#include "BgCtrl.hpp"
#include <Siv3D.hpp>
#include <abyss/params/UI/Title/BgParam.hpp>

namespace abyss::UI::Title::BackGround
{
    BgCtrl::BgCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_timer(BgParam::Common::TimeSec)
    {}
    void BgCtrl::onStart()
    {
        m_timer.start();
    }
    double BgCtrl::time0_1() const
    {
        return m_timer.progress0_1();
    }
    bool BgCtrl::isEnd() const
    {
        return m_timer.reachedZero();
    }
    s3d::Vec2 BgCtrl::getPos() const
    {
        return EaseIn(Easing::Linear, Scene::CenterF(), BgParam::BackGround::EndPos, this->time0_1());
    }
    s3d::Vec2 BgCtrl::getAtlantisPos() const
    {
        return EaseIn(Easing::Linear, BgParam::Atlantis::StartPos, Scene::CenterF(), this->time0_1());
    }
}
