#include "IRoomMove.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/Camera/Camera.hpp>
#include <abyss/controllers/Stage/Stage.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>

namespace abyss::Event::RoomMove
{
    IRoomMove::IRoomMove(const RoomModel& nextRoom, double animeMilliSec):
        m_nextRoom(nextRoom),
        m_animation(false, [this] {return m_pManager->getModule<GlobalTime>()->timeMicroSec(); }),
        m_animeMilliSec(animeMilliSec)
    {}
    void IRoomMove::init()
    {
        // 移動開始
        this->start();
        m_pManager->getModule<Camera>()->setRoom(m_nextRoom);
        m_pManager->getModule<Stage>()->checkOut();

    }
    bool IRoomMove::update([[maybe_unused]]double dt)
    {
        // todo カメラの座標更新
        // todo プレイヤーの座標更新
        return !this->isEnd();
    }
    void IRoomMove::onEnd()
    {
        this->onMoveEnd();
        m_pManager->getModule<Camera>()->applyNextRoom();
        m_pManager->getModule<Stage>()->checkIn();
    }
    double IRoomMove::elapsed() const
    {
        return s3d::Min<double>(m_animation.ms(), m_animeMilliSec) / m_animeMilliSec;
    }
    bool IRoomMove::isActive() const
    {
        return m_animation.isStarted();
    }
    bool IRoomMove::isEnd() const
    {
        return m_animation.ms() >= m_animeMilliSec;
    }
    void IRoomMove::start()
    {
        m_animation.start();
    }
}
