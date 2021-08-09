#include "RoomMoveCtrl.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Event/base/IEvent.hpp>

#include <abyss/utils/StopwatchEx/StopwatchEx.hpp>

namespace abyss::Event::RoomMove
{
    RoomMoveCtrl::RoomMoveCtrl(
        IEvent* pEvent,
        std::unique_ptr<IRoomMoveCallback> callback,
        const RoomModel& nextRoom,
        double animeMilliSec
    ):
        m_pEvent(pEvent),
        m_callback(std::move(callback)),
        m_nextRoom(nextRoom),
        m_animeMilliSec(animeMilliSec)
    {}
    void RoomMoveCtrl::setup(Executer executer)
    {
    }
    void RoomMoveCtrl::onStart()
    {
        auto roomManager = m_pEvent->getModule<RoomManager>();
        roomManager->setNextRoom(m_nextRoom);

        m_callback->onMoveStart();
        m_pEvent->getModule<Stage>()->checkOut();
    }
    void RoomMoveCtrl::onEnd()
    {
        m_callback->onMoveEnd();
        m_pEvent->getModule<RoomManager>()->applyNextRoom();
        m_pEvent->getModule<Stage>()->checkIn();
    }
    Coro::Task<> RoomMoveCtrl::onExecute()
    {
        StopwatchEx sw(true, m_pEvent->getModule<GlobalTime>()->clock());

        while (true) {
            auto elapsed = s3d::Min<double>(sw.ms(), m_animeMilliSec) / m_animeMilliSec;
            m_callback->onMoveUpdate(elapsed);

            // カメラの座標更新
            m_pEvent->getModule<Camera>()->setPos(m_callback->calcCameraPos());
            // プレイヤーの座標更新
            m_pEvent->getModule<Actor::Player::PlayerManager>()->setPos(m_callback->calcPlayerPos());

            if (sw.ms() >= m_animeMilliSec) {
                break;
            }
            co_yield{};
        }
        co_return;
    }
}
