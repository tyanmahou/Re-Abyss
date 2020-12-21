#include "ICameraWork.hpp"
#include <abyss/modules/Manager/Manager.hpp>
#include <abyss/modules/GlobalTime/GlobalTime.hpp>

namespace abyss
{
    using namespace s3d;

    ICameraWork::ICameraWork(double animeMilliSec) :
        m_animation(false, [this] {return m_pManager->getModule<GlobalTime>()->timeMicroSec(); }),
        m_animeMilliSec(animeMilliSec),
        m_pManager(nullptr)
    {}

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