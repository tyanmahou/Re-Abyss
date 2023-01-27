#include <abyss/components/Novel/RoomGarder/Builder.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Novel/base/Engine.hpp>
#include <abyss/components/Novel/RoomGarder/SignalCtrl.hpp>
#include <abyss/components/Novel/RoomGarder/Command/Setup.hpp>
#include <abyss/components/Novel/RoomGarder/Command/Teardown.hpp>
#include <abyss/components/Novel/Common/TalkCtrl.hpp>

namespace abyss::Novel::RoomGarder
{
    void Builder::Setup(TalkObj* pTalk)
    {
        pTalk->attach<SignalCtrl>(pTalk);

        pTalk->engine()->addCommand<RoomGarder::Setup>();
    }
    void Builder::Appear::Start(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand([](TalkObj* p) {
            p->find<TalkCtrl>()->request();
        });
    }
    void Builder::Appear::End(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand([](TalkObj* p) {
            p->find<TalkCtrl>()->resume();
        });
    }
    void Builder::Disappear::Start(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand([](TalkObj* p) {
            p->find<TalkCtrl>()->request();
        });
    }
    void Builder::Disappear::End(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand([](TalkObj* p) {
            p->find<TalkCtrl>()->resume();
        });
    }
    void Builder::Teardown(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<RoomGarder::Teardown>();
    }
}
