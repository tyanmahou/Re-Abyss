#include <abyss/components/Novel/CodeZeroDemo/Builder.hpp>

#include <abyss/components/Novel/CodeZeroDemo/SignalCtrl.hpp>
#include <abyss/components/Novel/CodeZeroDemo/Command/AppearStart.hpp>
#include <abyss/components/Novel/CodeZeroDemo/Command/AppearEnd.hpp>
#include <abyss/components/Novel/CodeZeroDemo/Command/DisappearStart.hpp>
#include <abyss/components/Novel/CodeZeroDemo/Command/DisappearEnd.hpp>
#include <abyss/components/Novel/CodeZeroDemo/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Novel/base/Engine.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    void Builder::Setup(TalkObj* pTalk)
    {
        pTalk->attach<SignalCtrl>(pTalk);

    }
    void Builder::Appear::Start(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<CodeZeroDemo::AppearStart>();
    }
    void Builder::Appear::End(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<CodeZeroDemo::AppearEnd>();
    }
    void Builder::Disappear::Start(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<CodeZeroDemo::DisappearStart>();
    }
    void Builder::Disappear::End(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<CodeZeroDemo::DisappearEnd>();
    }
    void Builder::Teardown(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<CodeZeroDemo::Teardown>();
    }
}
