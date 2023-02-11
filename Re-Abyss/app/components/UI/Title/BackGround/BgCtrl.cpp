#include <abyss/components/UI/Title/BackGround/BgCtrl.hpp>
#include <abyss/modules/UI/base/UIObj.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/params/UI/Title/BgParam.hpp>
#include <abyss/views/util/Anchor/AnchorUtil.hpp>
#include <Siv3D.hpp>

namespace abyss::UI::Title::BackGround
{
    BgCtrl::BgCtrl(UIObj* pUi):
        m_pUi(pUi),
        m_timer(BgParam::Common::TimeSec, StartImmediately::No, pUi->getModule<GlobalTime>())
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
        return AnchorUtil::FromCc(EaseIn(Easing::Linear, { 0, 0 }, BgParam::BackGround::EndPos, this->time0_1()));
    }
    s3d::Vec2 BgCtrl::getAtlantisPos() const
    {
        return AnchorUtil::FromCc(EaseIn(Easing::Linear, BgParam::Atlantis::StartPos, {0, 0}, this->time0_1()));
    }
}
