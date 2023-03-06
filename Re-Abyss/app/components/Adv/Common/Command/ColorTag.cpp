#include <abyss/components/Adv/Common/Command/ColorTag.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/SentenceCtrl.hpp>

namespace abyss::Adv
{
    ColorTag::ColorTag(AdvObj* pObj, const s3d::Optional<s3d::ColorF>& color):
        m_pObj(pObj),
        m_color(color)
    {}
    void ColorTag::onStart()
    {
        m_pObj->sentence()->setColor(m_color);
    }
    Coro::Fiber<> ColorTag::onCommand()
    {
        co_return;
    }
}
