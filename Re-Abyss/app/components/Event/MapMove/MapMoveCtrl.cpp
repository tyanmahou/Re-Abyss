#include <abyss/components/Event/MapMove/MapMoveCtrl.hpp>
#include <abyss/modules/Event/base/EventObj.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Camera/CameraFix/base/ICameraFix.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Actor/Player/PlayerManager.hpp>

#include <abyss/modules/Cycle/CycleMaster.hpp>
#include <abyss/components/Cycle/Main/Master.hpp>

#include <Siv3D.hpp>
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
        s3d::Vec2 apply([[maybe_unused]] const s3d::Vec2& target) const override
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
namespace abyss::Event::MapMove
{
    MapMoveCtrl::MapMoveCtrl(
        EventObj* pEvent,
        std::unique_ptr<IMapMoveCallback> callback,
        const LinkData& link,
        double animeMilliSec
    ) :
        m_pEvent(pEvent),
        m_callback(std::move(callback)),
        m_link(link),
        m_animeMilliSec(animeMilliSec)
    {
    }
    void MapMoveCtrl::setup([[maybe_unused]]Executer executer)
    {
    }
    void MapMoveCtrl::onStart()
    {
        m_callback->onMoveStart();
        m_pEvent->getModule<Stage>()->checkOut();
    }
    void MapMoveCtrl::onEnd()
    {
        m_callback->onMoveEnd();
    }
    Coro::Fiber<> MapMoveCtrl::onExecute()
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
            m_pEvent->getModule<Actor::Player::PlayerManager>()->setCenterPos(m_callback->calcPlayerPos());

            if (sw.ms() >= m_animeMilliSec) {
                break;
            }
            co_yield{};
        }
        m_pEvent->getModule<Camera>()->removeCameraFix(cameraFix);

        // マップ移動
        m_pEvent->getModule<CycleMaster>()
            ->find<Cycle::Main::Master>()
            ->moveStage(m_link.link, m_link.startId);
        co_return;
    }
}
