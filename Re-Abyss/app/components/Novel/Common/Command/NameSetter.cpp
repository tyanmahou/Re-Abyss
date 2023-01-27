#include <abyss/components/Novel/Common/Command/NameSetter.hpp>
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Novel/base/Engine.hpp>
namespace abyss::Novel
{
    NameSetter::NameSetter(TalkObj* pTalk, const Name& name):
        m_pTalk(pTalk),
        m_name(name)
    {}

    void NameSetter::onStart()
    {
        m_pTalk->engine()->setName(m_name);
    }

    Coro::Fiber<> NameSetter::onCommand()
    {
        co_return;
    }
}
