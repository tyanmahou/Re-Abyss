#include <abyss/components/Novel/RoomGarder/Command/Setup.hpp>

#include <abyss/modules/Novel/base/TalkObj.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Sound/Sound.hpp>
#include <abyss/commons/Path.hpp>

namespace abyss::Novel::RoomGarder
{
    Setup::Setup(TalkObj* pTalk):
        m_pTalk(pTalk)
    {}

    void Setup::onStart()
    {
        m_pTalk->getModule<RoomManager>()->requestRoomGarder();
        m_pTalk->getModule<Sound>()->play(Path::SoundPath + U"bgm/Main/Common/RoomGarder.aas");
    }

    Coro::Task<> Setup::onCommand()
    {
        co_return;
    }
}
