#include <abyss/components/Novel/CodeZeroDemo/Builder.hpp>

#include <abyss/components/Novel/CodeZeroDemo/SignalCtrl.hpp>


#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

namespace abyss::Novel::CodeZeroDemo
{
    void Builder::Setup(TalkObj* pTalk)
    {
        pTalk->attach<SignalCtrl>(pTalk);

    }
    void Builder::Appear::Start(TalkObj* pTalk)
    {
    }
    void Builder::Appear::End(TalkObj* pTalk)
    {
    }
    void Builder::Disappear::Start(TalkObj* pTalk)
    {
    }
    void Builder::Disappear::End(TalkObj* pTalk)
    {
    }
    void Builder::Teardown(TalkObj* pTalk)
    {
    }
}
