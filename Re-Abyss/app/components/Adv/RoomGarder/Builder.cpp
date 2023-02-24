#include <abyss/components/Adv/RoomGarder/Builder.hpp>

#include <abyss/modules/Adv/base/AdvObj.hpp>
#include <abyss/modules/Adv/base/Engine.hpp>
#include <abyss/components/Adv/RoomGarder/SignalCtrl.hpp>
#include <abyss/components/Adv/RoomGarder/Command/Setup.hpp>
#include <abyss/components/Adv/RoomGarder/Command/Teardown.hpp>
#include <abyss/components/Adv/Common/TalkCtrl.hpp>

namespace abyss::Adv::RoomGarder
{
    void Builder::Setup(AdvObj* pObj)
    {
        pObj->attach<SignalCtrl>(pObj);

        pObj->engine()->addCommand<RoomGarder::Setup>();
    }
    void Builder::Appear::Start(AdvObj* pObj)
    {
        pObj->engine()->addCommand([](AdvObj* p) {
            p->find<TalkCtrl>()->request();
        });
    }
    void Builder::Appear::End(AdvObj* pObj)
    {
        pObj->engine()->addCommand([](AdvObj* p) {
            p->find<TalkCtrl>()->resume();
        });
    }
    void Builder::Disappear::Start(AdvObj* pObj)
    {
        pObj->engine()->addCommand([](AdvObj* p) {
            p->find<TalkCtrl>()->request();
        });
    }
    void Builder::Disappear::End(AdvObj* pObj)
    {
        pObj->engine()->addCommand([](AdvObj* p) {
            p->find<TalkCtrl>()->resume();
        });
    }
    void Builder::Teardown(AdvObj* pObj)
    {
        pObj->engine()->addCommand<RoomGarder::Teardown>();
    }
}
