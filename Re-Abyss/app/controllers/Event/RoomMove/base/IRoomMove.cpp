#include "IRoomMove.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/GlobalTime/GlobalTime.hpp>
namespace abyss::Event::RoomMove
{
    IRoomMove::IRoomMove(double animeMilliSec):
        m_animation(false, [this] {return m_pManager->getModule<GlobalTime>()->timeMicroSec(); }),
        m_animeMilliSec(animeMilliSec)
    {}
    void IRoomMove::init()
    {}
    bool IRoomMove::update([[maybe_unused]]double dt)
    {
        // todo カメラの座標更新
        // todo プレイヤーの座標更新
        return !this->isEnd();
    }
    void IRoomMove::onEnd()
    {}
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
