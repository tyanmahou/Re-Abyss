#include <abyss/components/Novel/RoomGarder/Builder.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/components/Novel/base/Engine.hpp>
#include <abyss/components/Novel/RoomGarder/SignalCtrl.hpp>
#include <abyss/components/Novel/RoomGarder/Command/Setup.hpp>
#include <abyss/components/Novel/RoomGarder/Command/Teardown.hpp>

namespace abyss::Novel::RoomGarder
{
    void Builder::Setup(TalkObj* pTalk)
    {
        pTalk->attach<SignalCtrl>(pTalk);

        pTalk->engine()->addCommand<RoomGarder::Setup>();
    }
    void Builder::Teardown(TalkObj* pTalk)
    {
        pTalk->engine()->addCommand<RoomGarder::Teardown>();
    }
}
