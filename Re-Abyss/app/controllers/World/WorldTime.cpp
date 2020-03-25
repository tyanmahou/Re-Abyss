#include "WorldTime.hpp"
#include <Siv3D/Stopwatch.hpp>

namespace abyss
{
    using namespace s3d;
    class WorldTime::Impl
    {
    private:
        Stopwatch m_stopwatch{true};
        double m_timeScale = 1.0;
        double m_totalTimeSec = 0.0;
        double m_deltaTimeSec = 0.0;

        double m_currentRealTime = 0.0;
    public:
        void update()
        {
            auto prevTime = m_currentRealTime;

            m_currentRealTime = m_stopwatch.sF();
            m_deltaTimeSec = (m_currentRealTime - prevTime) * m_timeScale;
            m_totalTimeSec += m_deltaTimeSec;
        }
        double time() const
        {
            return m_totalTimeSec;
        }
        double deltaTime() const
        {
            return m_deltaTimeSec;
        }
        Duration elapsed() const
        {
            return Duration(m_totalTimeSec);
        }
        Microseconds timeMicroSec() const
        {
            return DurationCast<Microseconds>(elapsed());
        }

        void pause()
        {
            m_stopwatch.pause();
        }

        void resume()
        {
            m_stopwatch.resume();
        }

        void setTimeScale(double timeScale)
        {
            m_timeScale = timeScale;
        }
    };

    WorldTime::WorldTime():
        m_pImpl(std::make_unique<Impl>())
    {}
    void WorldTime::Update()
    {
        return Instance()->m_pImpl->update();
    }
    double WorldTime::Time()
    {
        return Instance()->m_pImpl->time();
    }
    s3d::Microseconds WorldTime::TimeMicroSec()
    {
        return Instance()->m_pImpl->timeMicroSec();
    }
    double WorldTime::DeltaTime()
    {
        return Instance()->m_pImpl->deltaTime();
    }
    void WorldTime::Pause()
    {
        return Instance()->m_pImpl->pause();
    }
    void WorldTime::Resume()
    {
        return Instance()->m_pImpl->resume();
    }
    void WorldTime::SetTimeScale(double timeScale)
    {
        return Instance()->m_pImpl->setTimeScale(timeScale);
    }
}
