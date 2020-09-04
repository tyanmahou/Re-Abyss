#include "GlobalTime.hpp"
#include <Siv3D/Stopwatch.hpp>
#include <Siv3D/Math.hpp>
#include <Siv3D/Array.hpp>
namespace abyss
{
    using namespace s3d;
    class GlobalTime::Impl
    {
    private:
        Stopwatch m_stopwatch{ true };
        double m_timeScale = 1.0;
        s3d::Array<std::weak_ptr<GlobalTimeScaleModel>> m_timeScaleModels;
        double m_totalTimeSec = 0.0;
        double m_deltaTimeSec = 0.0;

        double m_currentRealTime = 0.0;
    public:
        void update()
        {
            auto prevTime = m_currentRealTime;

            m_timeScale = 1.0;
            m_timeScaleModels.remove_if([](const std::weak_ptr<GlobalTimeScaleModel>& elm) {
                return elm.expired();
            });
            for (const auto& elm : m_timeScaleModels) {
                if (auto scale = elm.lock()) {
                    m_timeScale *= scale->getScale();
                }
            }
            m_currentRealTime = m_stopwatch.sF();
            m_deltaTimeSec = s3d::Min(m_currentRealTime - prevTime, 0.1) * m_timeScale;
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

        bool isPause()const
        {
            return m_stopwatch.isPaused();
        }

        void resume()
        {
            m_stopwatch.resume();
        }

        void addTimeScale(const std::shared_ptr<GlobalTimeScaleModel>& timeScale)
        {
            m_timeScaleModels.push_back(timeScale);
        }
    };

    GlobalTime::GlobalTime() :
        m_pImpl(std::make_unique<Impl>())
    {}
    GlobalTime::~GlobalTime()
    {}
    void GlobalTime::update() const
    {
        return m_pImpl->update();
    }
    double GlobalTime::time() const
    {
        return m_pImpl->time();
    }
    s3d::Microseconds GlobalTime::timeMicroSec() const
    {
        return m_pImpl->timeMicroSec();
    }
    double GlobalTime::deltaTime() const
    {
        return m_pImpl->deltaTime();
    }
    void GlobalTime::pause() const
    {
        return m_pImpl->pause();
    }
    void GlobalTime::resume() const
    {
        return m_pImpl->resume();
    }
    bool GlobalTime::isPuase() const
    {
        return m_pImpl->isPause();
    }
    void GlobalTime::addTimeScale(const std::shared_ptr<GlobalTimeScaleModel>& timeScale)
    {
        return m_pImpl->addTimeScale(timeScale);
    }
}

