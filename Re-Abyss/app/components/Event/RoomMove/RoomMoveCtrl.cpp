#include <abyss/components/Event/RoomMove/RoomMoveCtrl.hpp>
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Camera/CameraFix/base/ICameraFix.hpp>
#include <abyss/modules/Room/RoomManager.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>

#include <Siv3D/Stopwatch.hpp>

namespace
{
    using namespace abyss;

    class CameraFix : public ICameraFix
    {
    public:
        void setPos(const s3d::Vec2& pos)
        {
            m_pos = pos;
        }
        s3d::Vec2 apply([[maybe_unused]]const s3d::Vec2& target) const override
        {
            return m_pos;
        }

        CameraFixPriority priority() const override
        {
            return CameraFixPriority::RoomMove;
        }
    private:
        s3d::Vec2 m_pos;
    };
}
namespace abyss::Event::RoomMove
{
    RoomMoveCtrl::RoomMoveCtrl(
        EventObj* pEvent,
        std::unique_ptr<IRoomMoveCallback> callback,
        const Room::RoomData& nextRoom,
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
        roomManager->onCheckOut();
        m_pEvent->getModule<Stage>()->checkOut();
    }
    void RoomMoveCtrl::onEnd()
    {
        m_callback->onMoveEnd();
        auto roomManager = m_pEvent->getModule<RoomManager>();
        roomManager->applyNextRoom();
        roomManager->onCheckIn();
        m_pEvent->getModule<Stage>()->checkIn();
    }
    Coro::Fiber<> RoomMoveCtrl::onExecute()
    {
        s3d::Stopwatch sw(s3d::StartImmediately::Yes, m_pEvent->getModule<GlobalTime>());

        auto cameraFix = std::make_shared<CameraFix>();
        m_pEvent->getModule<Camera>()->addCameraFix(cameraFix);
        while (true) {
            auto elapsed = s3d::Min<double>(sw.ms(), m_animeMilliSec) / m_animeMilliSec;
            m_callback->onMoveUpdate(elapsed);

            // カメラの座標更新
            cameraFix->setPos(m_callback->calcCameraPos());
            // プレイヤーの座標更新
            m_pEvent->getModule<Actor::Player::PlayerManager>()->setPos(m_callback->calcPlayerPos());

            if (sw.ms() >= m_animeMilliSec) {
                break;
            }
            co_yield{};
        }
        m_pEvent->getModule<Camera>()->removeCameraFix(cameraFix);
        co_return;
    }
}
