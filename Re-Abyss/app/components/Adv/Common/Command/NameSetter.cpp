#include <abyss/components/Adv/Common/Command/NameSetter.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>
namespace abyss::Adv
{
    NameSetter::NameSetter(AdvObj* pTalk, const Name& name):
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
