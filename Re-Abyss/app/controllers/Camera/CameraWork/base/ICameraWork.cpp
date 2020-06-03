#include "ICameraWork.hpp"
#include <abyss/controllers/Manager/Manager.hpp>
#include <abyss/controllers/TimeController/TimeController.hpp>

namespace abyss
{
    using namespace s3d;

    ICameraWork::ICameraWork(Manager* pManager, double animeMilliSec) :
        m_animation(false, [pManager] {return pManager->getModule<TimeController>()->timeMicroSec(); }),
        m_animeMilliSec(animeMilliSec),
        m_pManager(pManager)
    {}

    Optional<Vec2> ICameraWork::calcPlayerPos() const
    {
        return s3d::none;
    }
    bool ICameraWork::isEnd() const
    {
        return m_animation.ms() >= m_animeMilliSec;
    }
    double ICameraWork::elapsed() const
    {
        return s3d::Min<double>(m_animation.ms(), m_animeMilliSec) / m_animeMilliSec;
    }
    bool ICameraWork::isActive() const
    {
        return m_animation.isStarted();
    }
    void ICameraWork::start()
    {
        m_animation.start();
    }
}