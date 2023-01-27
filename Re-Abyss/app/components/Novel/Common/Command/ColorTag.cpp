#include <abyss/components/Novel/Common/Command/ColorTag.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Novel/base/Engine.hpp>

namespace abyss::Novel
{
    ColorTag::ColorTag(TalkObj* pTalk, const s3d::Optional<s3d::ColorF>& color):
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
