#include <abyss/components/Novel/CodeZeroDemo/Builder.hpp>

#include <abyss/components/Novel/CodeZeroDemo/SignalCtrl.hpp>
#include <abyss/components/Novel/CodeZeroDemo/Command/AppearStart.hpp>
#include <abyss/components/Novel/CodeZeroDemo/Command/AppearEnd.hpp>
#include <abyss/components/Novel/CodeZeroDemo/Command/Teardown.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/components/Novel/base/Engine.hpp>

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
        pTalk->engine()->addCommand([](TalkObj* p) {
            p->getModule<Sound>()->stop(0.5s);
        });
    }
    void Builder::Disappear::End([[maybe_unused]]TalkObj* pTalk)
    {
    }
    void Builder::Teardown(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<CodeZeroDemo::Teardown>();
    }
}
