#include <abyss/components/Adv/CodeZeroDemo/Builder.hpp>

#include <abyss/components/Adv/CodeZeroDemo/SignalCtrl.hpp>
#include <abyss/components/Adv/CodeZeroDemo/Command/AppearStart.hpp>
#include <abyss/components/Adv/CodeZeroDemo/Command/AppearEnd.hpp>
#include <abyss/components/Adv/CodeZeroDemo/Command/DisappearStart.hpp>
#include <abyss/components/Adv/CodeZeroDemo/Command/DisappearEnd.hpp>
#include <abyss/components/Adv/CodeZeroDemo/Command/Teardown.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Process.hpp>

namespace abyss::Adv::CodeZeroDemo
{
    void Builder::Setup(AdvObj* pObj)
    {
        pObj->attach<SignalCtrl>(pObj);
    }
    void Builder::Appear::Start(AdvObj* pObj)
    {
        pObj->process()->addCommand<CodeZeroDemo::AppearStart>();
    }
    void Builder::Appear::End(AdvObj* pObj)
    {
        pObj->process()->addCommand<CodeZeroDemo::AppearEnd>();
    }
    void Builder::Disappear::Start(AdvObj* pObj)
    {
        pObj->process()->addCommand<CodeZeroDemo::DisappearStart>();
    }
    void Builder::Disappear::End(AdvObj* pObj)
    {
        pObj->process()->addCommand<CodeZeroDemo::DisappearEnd>();
    }
    void Builder::Teardown(AdvObj* pObj)
    {
        pObj->process()->addCommand<CodeZeroDemo::Teardown>();
    }
}
