#include "NameSetter.hpp"
#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>
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

    Coro::Task<> NameSetter::onCommand()
    {
        co_return;
    }
}