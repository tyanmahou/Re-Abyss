#include "IRoomMove.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/Camera/Camera.hpp>
#include <abyss/modules/Stage/Stage.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>
#include <abyss/modules/Actors/Player/PlayerManager.hpp>

namespace abyss::Event::RoomMove
{
    IRoomMove::IRoomMove(double animeMilliSec) :
        m_animation(false, [this] {return m_pManager->getModule<GlobalTime>()->timeMicroSec(); }),
        m_animeMilliSec(animeMilliSec)
    {}
    void IRoomMove::onStart()
    {
        // 移動開始
        this->start();
        this->onMoveStart();
        m_pManager->getModule<Stage>()->checkOut();

    }
    bool IRoomMove::update([[maybe_unused]] double dt)
    {
        // 更新
        this->onMoveUpdate(this->elapsed());

        // カメラの座標更新
        m_pManager->getModule<Camera>()->setPos(this->calcCameraPos());
        // プレイヤーの座標更新
        m_pManager->getModule<Actor::Player::PlayerManager>()->setPos(this->calcPlayerPos());

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