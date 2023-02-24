#include <abyss/components/Adv/Common/Command/ColorTag.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>

namespace abyss::Adv
{
    ColorTag::ColorTag(AdvObj* pTalk, const s3d::Optional<s3d::ColorF>& color):
        m_pTalk(pTalk),
        m_color(color)
    {}
    void ColorTag::onStart()
    {
        m_pTalk->engine()->setColor(m_color);
    }
    Coro::Fiber<> ColorTag::onCommand()
    {
        co_return;
    }
}
