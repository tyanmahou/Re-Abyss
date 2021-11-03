#include "ColorTag.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

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
    Coro::Task<> ColorTag::onCommand()
    {
        co_return;
    }
}
