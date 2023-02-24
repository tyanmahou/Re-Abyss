#include <abyss/components/Adv/Common/Command/NameSetter.hpp>
#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>
namespace abyss::Adv
{
    NameSetter::NameSetter(AdvObj* pObj, const Name& name):
        m_pObj(pObj),
        m_name(name)
    {}

    void NameSetter::onStart()
    {
        m_pObj->engine()->setName(m_name);
    }

    Coro::Fiber<> NameSetter::onCommand()
    {
        co_return;
    }
}
